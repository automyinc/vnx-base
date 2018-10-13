 /*************************************************************************
 * 
 *  [2017] - [2018] Automy Inc. 
 *  All Rights Reserved.
 * 
 * NOTICE:  All information contained herein is, and remains
 * the property of Automy Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Automy Incorporated
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Automy Incorporated.
 */

#ifndef INCLUDE_VNX_INPUTSTREAM_H_
#define INCLUDE_VNX_INPUTSTREAM_H_

#include <vnx/Type.h>

#include <cstring>
#include <unordered_map>


namespace vnx {

/// Base class for input streams
class InputStream {
public:
	virtual ~InputStream() {}
	
	/** \brief Reads up to \p len bytes into \p buf, returns number of bytes read.
	 * 
	 * @param buf Pointer to a buffer of \p len bytes.
	 * @param len Maximum number of bytes to read into \p buf.
	 * @return Number of bytes read into \p buf.
	 */
	virtual size_t read(void* buf, size_t len) = 0;
	
	/** \brief Returns total number of bytes read so far from stream.
	 * 
	 * In case of a file it returns the current read position, ie. seeking
	 * should be correctly handled.
	 */
	virtual size_t get_input_pos() const { return 0; }
	
};


/// Input stream for file descriptors
class BasicInputStream : public InputStream {
public:
	BasicInputStream() = default;
	
	BasicInputStream(int fd_) : fd(fd_) {}
	
	size_t read(void* buf, size_t len) override;
	
	void reset(int fd_) {
		fd = fd_;
	}
	
private:
	int fd = -1;
	
};


/// Input stream for files
class FileInputStream : public InputStream {
public:
	FileInputStream() = default;
	
	FileInputStream(FILE* file_) : file(file_) {}
	
	size_t read(void* buf, size_t len) override;
	
	size_t get_input_pos() const override;
	
	void reset(FILE* file_) {
		file = file_;
	}
	
private:
	FILE* file = 0;
	
};


/** \brief Input buffer for reading from a InputStream.
 * 
 * Used to speed up reading of small amounts of data, while also allowing
 * efficient reading of large amounts of data by bypassing the buffer.
 */
class InputBuffer {
public:
	InputBuffer(InputStream* stream_) : stream(stream_) {}
	
	InputBuffer(const InputBuffer& other) = delete;
	InputBuffer& operator=(const InputBuffer& other) = delete;
	
	/** \brief Reads \p len bytes and returns a pointer to the data.
	 * 
	 * Returns a pointer to the next available data and advances the internal pointer by \p len bytes.
	 * Reads new data from the stream if available bytes are less than \p len.
	 * Argument \p len cannot be larger than the buffer size, which is VNX_BUFFER_SIZE.
	 */
	const char* read(size_t len) {
		if(len > VNX_BUFFER_SIZE) {
			throw std::invalid_argument("read(): buffer too small");
		}
		while(end - pos < len) {
			// move left over data to the beginning
			::memmove(buffer, buffer + pos, end - pos);
			end -= pos;
			pos = 0;
			// read new data into the buffer (after the left over data)
			const size_t num_bytes = stream->read(buffer + end, VNX_BUFFER_SIZE - end);
			if(!num_bytes) {
				throw std::underflow_error("read(): EOF");
			}
			end += num_bytes;
		}
		char* res = buffer + pos;
		pos += len;
		return res;
	}
	
	/** \brief Reads \p len bytes into buffer given by \p buf.
	 * 
	 * This function blocks until all \p len bytes are read into the buffer \p buf.
	 * Used to read large chunks of data, potentially bypassing the buffer.
	 */
	void read(char* buf, size_t len) {
		const size_t left = end - pos;
		if(len < VNX_BUFFER_SIZE/2 || len < left) {
			// for small chunks just take it from the buffer if enough bytes are available
			::memcpy(buf, read(len), len);
			return;
		}
		if(left) {
			// first take whatever is left in the buffer
			::memcpy(buf, buffer + pos, left);
			buf += left;
			len -= left;
			pos = 0;
			end = 0;
		}
		while(len > 0) {
			// read remaining bytes directly from the stream
			const size_t num_bytes = stream->read(buf, len);
			if(!num_bytes) {
				throw std::underflow_error("read(): EOF");
			}
			buf += num_bytes;
			len -= num_bytes;
		}
	}
	
	/// Tries to have \p num_bytes ready in the buffer for reading
	void fetch(size_t num_bytes) {
		if(num_bytes > VNX_BUFFER_SIZE) {
			num_bytes = VNX_BUFFER_SIZE;
		}
		if(num_bytes > end) {
			num_bytes = stream->read(buffer + end, num_bytes - end);
			end += num_bytes;
		}
	}
	
	/// Resets the buffer, discarding any data left over
	void reset() {
		pos = 0;
		end = 0;
	}
	
	/// Returns number of bytes available in the buffer
	size_t get_num_avail() const {
		return end - pos;
	}
	
	/// Returns stream read position, while taking buffered data into account.
	size_t get_input_pos() const {
		return stream->get_input_pos() - get_num_avail();
	}
	
private:
	char buffer[VNX_BUFFER_SIZE];
	InputStream* stream = 0;
	size_t pos = 0;
	size_t end = 0;
	
};


/** \brief Input buffer to read typed data from a InputStream.
 * 
 * Used to read from a serialized data stream which was written by TypeOutput.
 */
class TypeInput : public InputBuffer {
public:
	TypeInput(InputStream* stream_) : InputBuffer::InputBuffer(stream_) {}
	
	/// Same as vnx::get_type_code()
	const TypeCode* get_type_code(Hash64 code_hash) const;
	
	/** \brief Resets the buffer and clears the type map.
	 * 
	 * Used as a way of creating a new TypeInput for the same stream in-place.
	 */
	void clear();
	
	std::unordered_map<Hash64, const TypeCode*> type_map;		/// for faster lock-free lookup
	
};


} // vnx

#endif /* INCLUDE_VNX_INPUTSTREAM_H_ */

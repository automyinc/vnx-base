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

#include <unordered_map>


namespace vnx {

class InputStream {
public:
	virtual ~InputStream() {}
	virtual size_t read(void* buf, size_t len) = 0;
};


class BasicInputStream : public InputStream {
public:
	BasicInputStream() : fd(-1) {}
	
	BasicInputStream(int fd_) : fd(fd_) {}
	
	size_t read(void* buf, size_t len);
	
	void reset(int fd_) {
		fd = fd_;
	}
	
private:
	int fd;
	
};


class FileInputStream : public InputStream {
public:
	FileInputStream() : file(0) {}
	
	FileInputStream(FILE* file_) : file(file_) {}
	
	size_t read(void* buf, size_t len);
	
	void reset(FILE* file_) {
		file = file_;
		num_read_since = 0;
	}
	
	size_t read_ahead_count = 0;
	
private:
	FILE* file = 0;
	size_t num_read_since = 0;
	
};


class MemoryInputStream : public InputStream {
public:
	MemoryInputStream() : buffer(0), size(0), pos(0) {}
	
	MemoryInputStream(const char* buffer_, size_t size_) : buffer(buffer_), size(size_), pos(0) {}
	
	size_t read(void* buf, size_t len);
	
	void reset(const char* buffer_, size_t size_) {
		buffer = buffer_;
		size = size_;
		pos = 0;
	}
	
private:
	const char* buffer;
	size_t size;
	size_t pos;
	
};


class InputBuffer {
public:
	InputBuffer(InputStream* stream_) : stream(stream_), pos(0), end(0) {}
	
	InputBuffer(const InputBuffer& other) = delete;
	InputBuffer& operator=(const InputBuffer& other) = delete;
	
	/*
	 * Get a pointer to the next available data and advance the internal pointer by "len" bytes.
	 * Reads new data from the stream if available bytes are less than "len".
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
			size_t num_bytes = stream->read(buffer + end, VNX_BUFFER_SIZE - end);
			if(!num_bytes) {
				throw std::underflow_error("read(): EOF");
			}
			end += num_bytes;
		}
		char* res = buffer + pos;
		pos += len;
		return res;
	}
	
	/*
	 * Read "len" bytes into memory given by "buf".
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
	
	/*
	 * Resets the buffer. Discards any data left over.
	 */
	void reset() {
		pos = 0;
		end = 0;
	}
	
	/*
	 * Get the number of bytes available in the buffer.
	 */
	size_t get_num_avail() const {
		return end - pos;
	}
	
private:
	InputStream* stream;
	char buffer[VNX_BUFFER_SIZE];
	size_t pos;
	size_t end;
	
};


class TypeInput : public InputBuffer {
public:
	TypeInput(InputStream* stream_) : InputBuffer::InputBuffer(stream_) {}
	
	const TypeCode* get_type_code(Hash64 code_hash) const;
	
	/*
	 * Resets the buffer and clears the type map.
	 * Used as a way of creating a new TypeInput in-place.
	 */
	void clear();
	
	std::unordered_map<Hash64, const TypeCode*> type_map;		// for faster lock-free lookup
	
};


} // vnx

#endif /* INCLUDE_VNX_INPUTSTREAM_H_ */

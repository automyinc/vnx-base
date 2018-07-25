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

#ifndef INCLUDE_VNX_OUTPUTSTREAM_H_
#define INCLUDE_VNX_OUTPUTSTREAM_H_

#include <vnx/Type.h>

#include <unordered_map>


namespace vnx {

class OutputStream {
public:
	virtual ~OutputStream() {}
	virtual void write(const void* buf, size_t len) = 0;
	virtual size_t get_output_pos() const = 0;
};


class BasicOutputStream : public OutputStream {
public:
	BasicOutputStream() : fd(-1) {}
	
	BasicOutputStream(int fd_) : fd(fd_) {}
	
	void write(const void* buf, size_t len);
	
	size_t get_output_pos() const { return 0; }
	
	void reset(int fd_) {
		fd = fd_;
	}
	
private:
	int fd;
	
};


class FileOutputStream : public OutputStream {
public:
	FileOutputStream() : file(0) {}
	
	FileOutputStream(FILE* file_) : file(file_) {}
	
	void write(const void* buf, size_t len);
	
	size_t get_output_pos() const { return ::ftell(file); }
	
	void reset(FILE* file_) {
		file = file_;
	}
	
private:
	FILE* file;
	
};


class SocketOutputStream : public OutputStream {
public:
	SocketOutputStream() : fd(-1) {}
	
	SocketOutputStream(int fd_) : fd(fd_) {}
	
	void write(const void* buf, size_t len);
	
	size_t get_output_pos() const { return 0; }
	
	void reset(int fd_) {
		fd = fd_;
	}
	
private:
	int fd;
	
};


class MemoryOutputStream : public OutputStream {
public:
	MemoryOutputStream(char* buf, size_t size) : buffer(buf), size(size), pos(0) {}
	
	void write(const void* buf, size_t len);
	
	size_t get_output_pos() const { return pos; }
	
private:
	char* buffer;
	size_t size;
	size_t pos;
	
};


class OutputBuffer {
public:
	OutputBuffer(OutputStream* stream_) : stream(stream_), pos(0) {}
	
	OutputBuffer(const OutputBuffer& other) = delete;
	OutputBuffer& operator=(const OutputBuffer& other) = delete;
	
	/*
	 * Get a pointer to at least "len" number of bytes in the buffer.
	 * Will flush the buffer to the stream if not enough space available.
	 */
	char* write(size_t len) {
		if(len > VNX_BUFFER_SIZE) {
			throw std::invalid_argument("write(): buffer too small");
		}
		if(VNX_BUFFER_SIZE - pos < len) {
			flush();
		}
		char* res = buffer + pos;
		pos += len;
		return res;
	}
	
	/*
	 * Write "len" number of bytes given by "data" to the stream.
	 * Used to write large chunks of data, potentially bypassing the buffer.
	 */
	void write(const void* data, size_t len) {
		if(len < VNX_BUFFER_SIZE/2) {
			::memcpy(write(len), data, len);
		} else {
			flush();
			stream->write(data, len);
		}
	}
	
	/*
	 * Flush the buffer to the stream.
	 * Used to make sure that all data is actually written to the stream.
	 */
	void flush() {
		if(pos > 0) {
			stream->write(buffer, pos);
			pos = 0;
		}
	}
	
	/*
	 * Resets the buffer. Discards any data left over.
	 */
	void reset() {
		pos = 0;
	}
	
	/*
	 * Returns the buffer size.
	 */
	size_t get_buffer_size() const {
		return VNX_BUFFER_SIZE;
	}
	
	/*
	 * Returns the number of bytes currently left in the buffer.
	 */
	size_t get_buffer_pos() const {
		return pos;
	}
	
	/*
	 * Returns the number of bytes that have been written to the stream already, plus what is left in the buffer.
	 */
	size_t get_output_pos() const {
		return stream->get_output_pos() + pos;
	}
	
private:
	OutputStream* stream;
	char buffer[VNX_BUFFER_SIZE];
	size_t pos;
	
};


class TypeOutput : public OutputBuffer {
public:
	TypeOutput(OutputStream* stream_) : OutputBuffer::OutputBuffer(stream_) {}
	
	void write_type_code(const TypeCode* type_code);
	
	/*
	 * Resets the buffer and clears the type map.
	 * Used as a way of creating a new TypeOutput in-place.
	 */
	void clear();
	
	// to keep track of which type codes already have been written to the stream
	std::unordered_map<uint64_t, const TypeCode*> type_map;
	
	// to keep track of where the type codes have been written
	std::vector<uint64_t> type_code_positions;
	
};


} // vnx

#endif /* INCLUDE_VNX_OUTPUTSTREAM_H_ */

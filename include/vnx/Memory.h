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

#ifndef INCLUDE_VNX_MEMORY_H
#define INCLUDE_VNX_MEMORY_H

#include <vnx/Type.h>
#include <vnx/InputStream.h>
#include <vnx/OutputStream.h>


namespace vnx {

class Memory {
public:
	struct chunk_t {
		chunk_t* next = 0;
		char* data = 0;
		size_t size = 0;
	};
	
	chunk_t* front = 0;
	chunk_t* back = 0;
	
	Memory() = default;
	
	~Memory() {
		clear();
	}
	
	Memory(const Memory& other) {
		*this = other;
	}
	
	Memory& operator=(const Memory& other);
	
	bool operator==(const Memory& other) const;
	
	bool operator!=(const Memory& other) const;
	
	bool operator<(const Memory& other) const;
	
	bool operator>(const Memory& other) const;
	
	bool empty() const {
		return front == 0;
	}
	
	Hash64 get_hash() const;
	
	char* add_chunk(size_t len);
	
	size_t get_size() const;
	
	void write(OutputBuffer& out) const;
	
	void clear();
	
};


class MemoryOutputStream : public OutputStream {
public:
	MemoryOutputStream(Memory* data_) : data(data_) {
		pos = data->get_size();
	}
	
	void write(const void* buf, size_t len) {
		::memcpy(data->add_chunk(len), buf, len);
		pos += len;
	}
	
	size_t get_output_pos() const {
		return pos;
	}

private:
	Memory* data = 0;
	size_t pos = 0;
	
};


class MemoryInputStream : public InputStream {
public:
	MemoryInputStream(const Memory* data_) {
		chunk = data_->front;
	}
	
	size_t read(void* buf, size_t len) {
		if(!chunk) {
			return 0;
		}
		const size_t left = chunk->size - pos;
		if(len > left) {
			len = left;
		}
		::memcpy(buf, chunk->data + pos, len);
		pos += len;
		if(pos >= chunk->size) {
			chunk = chunk->next;
			pos = 0;
		}
		return len;
	}

private:
	const Memory::chunk_t* chunk = 0;
	size_t pos = 0;
	
};


} // vnx

#endif /* INCLUDE_VNX_MEMORY_H */

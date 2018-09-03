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

#ifndef INCLUDE_VNX_BUFFER_H
#define INCLUDE_VNX_BUFFER_H

#include <vnx/package.hxx>
#include <vnx/InputStream.h>

#include <cstring>
 

namespace vnx {

class Buffer {
public:
	Buffer() = default;
	
	explicit Buffer(size_t init_capacity);
	
	Buffer(const Buffer& other);
	
	Buffer(const std::string& other);
	
	~Buffer();
	
	Buffer& operator=(const Buffer& other);
	
	Buffer& operator=(const std::string& other);
	
	void reserve(size_t new_capacity);
	
	void set_size(size_t new_size);
	
	size_t size() const {
		return size_;
	}
	
	size_t capacity() const {
		return capacity_;
	}
	
	void* data() {
		return data_;
	}
	
	const void* data() const {
		return data_;
	}
	
	void* data(size_t offset) {
		return ((char*)data_ + offset);
	}
	
	const void* data(size_t offset) const {
		return ((const char*)data_ + offset);
	}
	
	void release();
	
	void clear() {
		size_ = 0;
	}
	
	std::string as_string() const;
	
private:
	void* data_ = 0;
	size_t size_ = 0;
	size_t capacity_ = 0;
	
};


class BufferInputStream : public InputStream {
public:
	BufferInputStream(const Buffer* data_) : data(data_) {}
	
	size_t read(void* buf, size_t len) override;

private:
	const Buffer* data = 0;
	size_t pos = 0;
	
};


} // vnx

#endif // INCLUDE_VNX_BUFFER_H

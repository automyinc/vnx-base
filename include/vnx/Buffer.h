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

#include <cstring>
 

namespace vnx {

class Buffer {
public:
	Buffer() = default;
	
	explicit Buffer(size_t init_capacity) {
		reserve(init_capacity);
	}
	
	Buffer(const Buffer& other) {
		*this = other;
	}
	
	~Buffer() {
		if(data_) {
			::free(data_);
		}
	}
	
	Buffer& operator=(const Buffer& other) {
		reserve(other.capacity_);
		::memcpy(data_, other.data_, other.size_);
		set_size(other.size_);
		return *this;
	}
	
	Buffer& operator=(const std::string& other) {
		reserve(other.size());
		::memcpy(data_, other.data(), capacity_);
		set_size(capacity_);
		return *this;
	}
	
	void reserve(size_t new_capacity) {
		if(new_capacity > capacity_) {
			if(data_) {
				::free(data_);
			}
			data_ = ::malloc(new_capacity);
			capacity_ = new_capacity;
		}
	}
	
	void set_size(size_t new_size) {
		if(new_size > capacity_) {
			throw std::logic_error("Buffer::set_size(): new_size > capacity_");
		}
		size_ = new_size;
	}
	
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
	
	void release() {
		data_ = 0;
		size_ = 0;
		capacity_ = 0;
	}
	
	void clear() {
		size_ = 0;
	}
	
private:
	void* data_ = 0;
	size_t size_ = 0;
	size_t capacity_ = 0;
	
};


} // vnx

#endif // INCLUDE_VNX_BUFFER_H

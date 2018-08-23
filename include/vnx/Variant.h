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

#ifndef INCLUDE_VNX_VARIANT_H
#define INCLUDE_VNX_VARIANT_H

#include <vnx/package.hxx>
#include <vnx/Memory.h>
#include <vnx/Input.h>
#include <vnx/Output.h>
#include <vnx/Value.h>


namespace vnx {

class Variant {
public:
	Memory data;
	
	Variant() = default;
	
	Variant(const Variant& other) {
		*this = other;
	}
	
	template<typename T>
	Variant(const T& value) {
		assign(value);
	}
	
	static std::shared_ptr<Variant> create() {
		return std::make_shared<Variant>();
	}
	
	Variant& operator=(const Variant& other) = default;
	
	template<typename T>
	Variant& assign(const T& value) {
		clear();
		MemoryOutputStream stream(&data);
		TypeOutput out(&stream);
		vnx::write_dynamic(out, value);
		out.flush();
		return *this;
	}
	
	Variant& assign(const char value[]) {
		clear();
		MemoryOutputStream stream(&data);
		TypeOutput out(&stream);
		vnx::write_dynamic(out, std::string(value));
		out.flush();
		return *this;
	}
	
	template<typename T>
	Variant& operator=(const T& value) {
		assign(value);
		return *this;
	}
	
	template<typename T>
	T to() const {
		if(data.empty()) {
			return T();
		}
		MemoryInputStream stream(&data);
		TypeInput in(&stream);
		T value = T();
		vnx::read_dynamic(in, value);
		return value;
	}
	
	Hash64 get_hash() const { return data.get_hash(); }
	
	bool operator==(const Variant& other) const {
		return data == other.data;
	}
	
	bool operator!=(const Variant& other) const {
		return data != other.data;
	}
	
	bool operator<(const Variant& other) const {
		return data < other.data;
	}
	
	bool operator>(const Variant& other) const {
		return data > other.data;
	}
	
	operator bool() const {
		return to<bool>();
	}
	
	operator uint8_t() const {
		return to<uint8_t>();
	}
	
	operator uint16_t() const {
		return to<uint16_t>();
	}
	
	operator uint32_t() const {
		return to<uint32_t>();
	}
	
	operator uint64_t() const {
		return to<uint64_t>();
	}
	
	operator int8_t() const {
		return to<int8_t>();
	}
	
	operator int16_t() const {
		return to<int16_t>();
	}
	
	operator int32_t() const {
		return to<int32_t>();
	}
	
	operator int64_t() const {
		return to<int64_t>();
	}
	
	operator float32_t() const {
		return to<float32_t>();
	}
	
	operator float64_t() const {
		return to<float64_t>();
	}
	
	std::string to_string() const {
		return to<std::string>();
	}
	
	bool empty() const {
		return data.empty();
	}
	
	void clear() {
		data.clear();
	}
	
	friend std::ostream& operator<<(std::ostream& out, const Variant& value) {
		vnx::write(out, value);
		return out;
	}
	
	friend std::istream& operator>>(std::istream& in, Variant& value) {
		vnx::read(in, value);
		return in;
	}
	
};


} // vnx


namespace std {
	template<> struct hash<vnx::Variant> {
		size_t operator()(const vnx::Variant& x) const {
			return x.get_hash();
		}
	};
} // std

#endif /* INCLUDE_VNX_VARIANT_H */

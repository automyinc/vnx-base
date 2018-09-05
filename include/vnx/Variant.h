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
	
	static std::shared_ptr<Variant> create(const Variant& other) {
		return std::make_shared<Variant>(other);
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
	
	Variant& assign(const Variant& value) {
		*this = value;
		return *this;
	}
	
	Variant& assign(const char* str);
	
	Variant& assign(const char* str, size_t len);
	
	template<typename T>
	Variant& operator=(const T& value) {
		assign(value);
		return *this;
	}
	
	template<typename T>
	T to() const {
		if(empty()) {
			return T();
		}
		MemoryInputStream stream(&data);
		TypeInput in(&stream);
		T value;
		vnx::read_dynamic(in, value);
		return value;
	}
	
	template<typename T>
	void to(T& value) const {
		if(empty()) {
			value = T();
			return;
		}
		MemoryInputStream stream(&data);
		TypeInput in(&stream);
		vnx::read_dynamic(in, value);
	}
	
	/** \brief Computes a semantic 64-bit content hash
	 * 
	 * This hash is invariant against different byte order, different integer size and type,
	 * different array types and different list types.
	 * Internally ToBinaryString is used to transform the data before computing the hash.
	 */
	Hash64 get_hash() const;
	
	const uint16_t* get_code() const;
	
	bool operator==(const Variant& other) const;
	
	bool operator!=(const Variant& other) const;
	
	bool operator<(const Variant& other) const;
	
	bool operator>(const Variant& other) const;
	
	bool operator<=(const Variant& other) const;
	
	bool operator>=(const Variant& other) const;
	
	operator bool() const;
	
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
	
	bool empty() const {
		return data.empty();
	}
	
	bool is_null() const;
	
	bool is_long() const;
	
	bool is_ulong() const;
	
	bool is_double() const;
	
	bool is_integral() const;
	
	bool is_string() const;
	
	bool is_array() const;
	
	bool is_list() const;
	
	bool is_map() const;
	
	bool is_object() const;
	
	bool is_value() const;
	
	void clear() {
		data.clear();
	}
	
	std::string to_string() const {
		return vnx::to_string(*this);
	}
	
	std::string to_string_value() const {
		return vnx::to_string_value(*this);
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


template<>
bool Variant::to<bool>() const;

inline Variant::operator bool() const {
	return to<bool>();
}


} // vnx


namespace std {
	template<> struct hash<vnx::Variant> {
		size_t operator()(const vnx::Variant& x) const {
			return x.get_hash();
		}
	};
} // std

#endif /* INCLUDE_VNX_VARIANT_H */

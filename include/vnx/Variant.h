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

/** \brief Class to hold any possible value in serialized form.
 * 
 * Used as a generic variable, field or parameter.
 */
class Variant {
public:
	Memory data;		///< The serialized data
	
	/// Creates empty Variant
	Variant() = default;
	
	/// Performs deep-copy
	Variant(const Variant& other) {
		*this = other;
	}
	
	/// Create Variant with given value
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
	
	/// Performs deep-copy
	Variant& operator=(const Variant& other) = default;
	
	/// Assign new value
	template<typename T>
	Variant& assign(const T& value) {
		clear();
		MemoryOutputStream stream(&data);
		TypeOutput out(&stream);
		vnx::write_dynamic(out, value);
		out.flush();
		return *this;
	}
	
	/// Assign new value
	Variant& assign(const Variant& value) {
		*this = value;
		return *this;
	}
	
	/// Assign new null terminated string
	Variant& assign(const char* str);
	
	/// Assign new string with given length
	Variant& assign(const char* str, size_t len);
	
	/// Assign new value
	template<typename T>
	Variant& operator=(const T& value) {
		assign(value);
		return *this;
	}
	
	/// Convert value to type T
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
	
	/// Convert value to type T
	template<typename T>
	void to(T& value) const {
		value = to<T>();
	}
	
	/** \brief Computes a semantic 64-bit content hash
	 * 
	 * This hash is invariant against different byte order, different integer size and type,
	 * different array types and different list types.
	 * Internally ToBinaryString is used to transform the data before computing the hash.
	 */
	Hash64 get_hash() const;
	
	/// Returns type code of current value
	const uint16_t* get_code() const;
	
	bool operator==(const Variant& other) const;
	
	bool operator!=(const Variant& other) const;
	
	bool operator<(const Variant& other) const;
	
	bool operator>(const Variant& other) const;
	
	bool operator<=(const Variant& other) const;
	
	bool operator>=(const Variant& other) const;
	
	/** \brief Converts value to a bool.
	 * 
	 * CODE_NULL == false, otherwise normal C++ conversion applies.
	 */
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
	
	operator char() const {
		return to<char>();
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
	
	/** \brief Returns true if value is null, ie. CODE_NULL.
	 * 
	 * Note: Returns false for empty Variant also.
	 */
	bool is_null() const;
	
	/// Returns true if value is a signed or unsigned integer.
	bool is_long() const;
	
	/// Returns true if value is a unsigned integer.
	bool is_ulong() const;
	
	/// Returns true if value is a float or double.
	bool is_double() const;
	
	/// Returns true if value is an integer or a float/double.
	bool is_integral() const;
	
	/// Returns true if value is a string.
	bool is_string() const;
	
	/// Returns true if value is a static array. (CODE_ARRAY)
	bool is_array() const;
	
	/// Returns true if value is a dynamic array/list. (CODE_LIST)
	bool is_list() const;
	
	/// Returns true if value is a map. (CODE_MAP)
	bool is_map() const;
	
	/// Returns true if value is an Object. (CODE_OBJECT)
	bool is_object() const;
	
	/// Returns true if value is a Value. (CODE_ANY)
	bool is_value() const;
	
	/// Clear value, ie. make Variant empty.
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
	
	/// Returns reference to an empty Variant
	static const Variant& get_empty() {
		return empty_instance;
	}
	
private:
	static const Variant empty_instance;
	
};


/// See bool()
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

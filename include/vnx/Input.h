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

#ifndef INCLUDE_VNX_INPUT_H_
#define INCLUDE_VNX_INPUT_H_

#include <vnx/InputStream.h>

#include <sstream>


namespace vnx {

/// Skips the next value in the stream
void skip(TypeInput& in);

/// Skips the current value in the stream
void skip(TypeInput& in, const TypeCode* type_code, const uint16_t* code);

/// Bulk byte copy from in to out (out can be null)
void copy_bytes(TypeInput& in, TypeOutput* out, size_t num_bytes);

/// Copy next value from in to out (out can be null)
void copy(TypeInput& in, TypeOutput* out);

/// Copy rest of current value to out (out can be null)
void copy(TypeInput& in, TypeOutput* out, const TypeCode* type_code, const uint16_t* code);

/** \brief Reads dynamic code from the stream.
 * 
 * @param code Pointer to at least VNX_MAX_BYTE_CODE_SIZE uint16_t elements.
 * @return Size of the code read, in elements of uint16_t.
 */
uint16_t read_byte_code(TypeInput& in, uint16_t* code);

/// Converts little-endian to big-endian and big-endian to little-endian.
/// @{
inline bool flip_bytes(const bool& value) { return (value != 0); }
inline uint8_t flip_bytes(const uint8_t& value) { return value; }
inline uint16_t flip_bytes(const uint16_t& value) { return (value >> 8) | (value << 8); }
inline uint32_t flip_bytes(const uint32_t& value) { return uint32_t(flip_bytes(uint16_t(value >> 16))) | (uint32_t(flip_bytes(uint16_t(value))) << 16); }
inline uint64_t flip_bytes(const uint64_t& value) { return uint64_t(flip_bytes(uint32_t(value >> 32))) | (uint64_t(flip_bytes(uint32_t(value))) << 32); }
inline char flip_bytes(const char& value) { return value; }
inline int8_t flip_bytes(const int8_t& value) { return value; }
inline int16_t flip_bytes(const int16_t& value) { return int16_t(flip_bytes(uint16_t(value))); }
inline int32_t flip_bytes(const int32_t& value) { return int32_t(flip_bytes(uint32_t(value))); }
inline int64_t flip_bytes(const int64_t& value) { return int64_t(flip_bytes(uint64_t(value))); }
inline Hash64 flip_bytes(const Hash64& value) { return Hash64(flip_bytes(uint64_t(value))); }

inline float32_t flip_bytes(const float32_t& value) {
	uint32_t tmp;
	::memcpy(&tmp, &value, sizeof(float32_t));
	tmp = flip_bytes(tmp);
	float32_t out;
	::memcpy(&out, &tmp, sizeof(float32_t));
	return out;
}

inline float64_t flip_bytes(const float64_t& value) {
	uint64_t tmp;
	::memcpy(&tmp, &value, sizeof(float64_t));
	tmp = flip_bytes(tmp);
	float64_t out;
	::memcpy(&out, &tmp, sizeof(float64_t));
	return out;
}
/// @}

/** \brief Reads a value directly from the stream.
 * 
 * Used when it's known that a value of said type is to follow.
 */
/// @{
inline void read(TypeInput& in, bool& value) { value = *((uint8_t*)in.read(sizeof(uint8_t))); }
inline void read(TypeInput& in, uint8_t& value) { value = *((uint8_t*)in.read(sizeof(uint8_t))); }
inline void read(TypeInput& in, uint16_t& value) { value = *((uint16_t*)in.read(sizeof(uint16_t))); }
inline void read(TypeInput& in, uint32_t& value) { value = *((uint32_t*)in.read(sizeof(uint32_t))); }
inline void read(TypeInput& in, uint64_t& value) { value = *((uint64_t*)in.read(sizeof(uint64_t))); }
inline void read(TypeInput& in, char& value) { value = *((int8_t*)in.read(sizeof(int8_t))); }
inline void read(TypeInput& in, int8_t& value) { value = *((int8_t*)in.read(sizeof(int8_t))); }
inline void read(TypeInput& in, int16_t& value) { value = *((int16_t*)in.read(sizeof(int16_t))); }
inline void read(TypeInput& in, int32_t& value) { value = *((int32_t*)in.read(sizeof(int32_t))); }
inline void read(TypeInput& in, int64_t& value) { value = *((int64_t*)in.read(sizeof(int64_t))); }
inline void read(TypeInput& in, float32_t& value) { value = *((float32_t*)in.read(sizeof(float32_t))); }
inline void read(TypeInput& in, float64_t& value) { value = *((float64_t*)in.read(sizeof(float64_t))); }
inline void read(TypeInput& in, Hash64& value) { value = Hash64(*((uint64_t*)in.read(sizeof(uint64_t)))); }
/// @}

/** \brief Reads a value directly from the buffer.
 * 
 * Used when it's known that a value of said type is in the buffer.
 */
/// @{
inline void read_value(const void* buf, bool& value) { value = *((uint8_t*)buf); }
inline void read_value(const void* buf, uint8_t& value) { value = *((uint8_t*)buf); }
inline void read_value(const void* buf, uint16_t& value) { value = *((uint16_t*)buf); }
inline void read_value(const void* buf, uint32_t& value) { value = *((uint32_t*)buf); }
inline void read_value(const void* buf, uint64_t& value) { value = *((uint64_t*)buf); }
inline void read_value(const void* buf, char& value) { value = *((int8_t*)buf); }
inline void read_value(const void* buf, int8_t& value) { value = *((int8_t*)buf); }
inline void read_value(const void* buf, int16_t& value) { value = *((int16_t*)buf); }
inline void read_value(const void* buf, int32_t& value) { value = *((int32_t*)buf); }
inline void read_value(const void* buf, int64_t& value) { value = *((int64_t*)buf); }
inline void read_value(const void* buf, float32_t& value) { value = *((float32_t*)buf); }
inline void read_value(const void* buf, float64_t& value) { value = *((float64_t*)buf); }
inline void read_value(const void* buf, Hash64& value) { value = Hash64(*((uint64_t*)buf)); }
/// @}

/** \brief Reads a value of type \p code from the buffer.
 * 
 * Will try to convert value in case type != T.
 * If no conversion is possible \p value is default initialized.
 */
template<typename T>
void read_value(const void* buf, T& value, const uint16_t* code) {
	switch(code[0]) {
		case CODE_NULL: value = T(); return;
		case CODE_UINT8: value = *((const uint8_t*)buf); return;
		case CODE_UINT16: value = *((const uint16_t*)buf); return;
		case CODE_UINT32: value = *((const uint32_t*)buf); return;
		case CODE_UINT64: value = *((const uint64_t*)buf); return;
		case CODE_INT8: value = *((const int8_t*)buf); return;
		case CODE_INT16: value = *((const int16_t*)buf); return;
		case CODE_INT32: value = *((const int32_t*)buf); return;
		case CODE_INT64: value = *((const int64_t*)buf); return;
		case CODE_FLOAT: value = *((const float32_t*)buf); return;
		case CODE_DOUBLE: value = *((const float64_t*)buf); return;
		case CODE_ALT_UINT8: value = flip_bytes(*((const uint8_t*)buf)); return;
		case CODE_ALT_UINT16: value = flip_bytes(*((const uint16_t*)buf)); return;
		case CODE_ALT_UINT32: value = flip_bytes(*((const uint32_t*)buf)); return;
		case CODE_ALT_UINT64: value = flip_bytes(*((const uint64_t*)buf)); return;
		case CODE_ALT_INT8: value = flip_bytes(*((const int8_t*)buf)); return;
		case CODE_ALT_INT16: value = flip_bytes(*((const int16_t*)buf)); return;
		case CODE_ALT_INT32: value = flip_bytes(*((const int32_t*)buf)); return;
		case CODE_ALT_INT64: value = flip_bytes(*((const int64_t*)buf)); return;
		case CODE_ALT_FLOAT: value = flip_bytes(*((const float32_t*)buf)); return;
		case CODE_ALT_DOUBLE: value = flip_bytes(*((const float64_t*)buf)); return;
		default: value = T();
	}
}

/** \brief Reads a static array from the buffer.
 * 
 * Directly compatible with CODE_ARRAY.
 */
template<typename T, size_t N>
void read_value(const char* buf, std::array<T, N>& array, const uint16_t* code) {
	size_t size = 0;
	switch(code[0]) {
		case CODE_ARRAY: size = code[1]; break;
		case CODE_ALT_ARRAY: size = flip_bytes(code[1]); break;
	}
	size = size <= N ? size : N;
	const size_t value_size = get_value_size(code[2]);
	for(size_t i = 0; i < size; ++i) {
		read_value(buf + i * value_size, array[i], code + 2);
	}
	for(size_t i = size; i < N; ++i) {
		array[i] = T();
	}
}

template<typename T>
void read_dynamic_value(TypeInput& in, T& value);

/** \brief Reads a value of type \p code from the stream.
 * 
 * Will try to convert value in case type != T.
 * In case no conversion is possible \p value is default initialized and the data skipped.
 */
template<typename T>
void read_value(TypeInput& in, T& value, const TypeCode* type_code, const uint16_t* code) {
	switch(code[0]) {
		case CODE_NULL: value = T(); return;
		case CODE_UINT8: value = *((const uint8_t*)in.read(sizeof(uint8_t))); return;
		case CODE_UINT16: value = *((const uint16_t*)in.read(sizeof(uint16_t))); return;
		case CODE_UINT32: value = *((const uint32_t*)in.read(sizeof(uint32_t))); return;
		case CODE_UINT64: value = *((const uint64_t*)in.read(sizeof(uint64_t))); return;
		case CODE_INT8: value = *((const int8_t*)in.read(sizeof(int8_t))); return;
		case CODE_INT16: value = *((const int16_t*)in.read(sizeof(int16_t))); return;
		case CODE_INT32: value = *((const int32_t*)in.read(sizeof(int32_t))); return;
		case CODE_INT64: value = *((const int64_t*)in.read(sizeof(int64_t))); return;
		case CODE_FLOAT: value = *((const float32_t*)in.read(sizeof(float32_t))); return;
		case CODE_DOUBLE: value = *((const float64_t*)in.read(sizeof(float64_t))); return;
		case CODE_ALT_UINT8: value = flip_bytes(*((const uint8_t*)in.read(sizeof(uint8_t)))); return;
		case CODE_ALT_UINT16: value = flip_bytes(*((const uint16_t*)in.read(sizeof(uint16_t)))); return;
		case CODE_ALT_UINT32: value = flip_bytes(*((const uint32_t*)in.read(sizeof(uint32_t)))); return;
		case CODE_ALT_UINT64: value = flip_bytes(*((const uint64_t*)in.read(sizeof(uint64_t)))); return;
		case CODE_ALT_INT8: value = flip_bytes(*((const int8_t*)in.read(sizeof(int8_t)))); return;
		case CODE_ALT_INT16: value = flip_bytes(*((const int16_t*)in.read(sizeof(int16_t)))); return;
		case CODE_ALT_INT32: value = flip_bytes(*((const int32_t*)in.read(sizeof(int32_t)))); return;
		case CODE_ALT_INT64: value = flip_bytes(*((const int64_t*)in.read(sizeof(int64_t)))); return;
		case CODE_ALT_FLOAT: value = flip_bytes(*((const float32_t*)in.read(sizeof(float32_t)))); return;
		case CODE_ALT_DOUBLE: value = flip_bytes(*((const float64_t*)in.read(sizeof(float64_t)))); return;
		case CODE_DYNAMIC:
		case CODE_ALT_DYNAMIC: read_dynamic_value(in, value); return;
		default:
			value = T();
			skip(in, type_code, code);
	}
}

/** \brief Reads a dynamic value from the stream.
 * 
 * Directly compatible with CODE_DYNAMIC.
 */
template<typename T>
void read_dynamic_value(TypeInput& in, T& value) {
	uint16_t code[VNX_MAX_BYTE_CODE_SIZE];
	read_byte_code(in, code);
	read_value(in, value, 0, code);
}

/// Reads a value of type \p code from the stream.
/// @{
inline void read(TypeInput& in, bool& value, const TypeCode* type_code, const uint16_t* code) {
	read_value(in, value, type_code, code);
}
inline void read(TypeInput& in, uint8_t& value, const TypeCode* type_code, const uint16_t* code) {
	read_value(in, value, type_code, code);
}
inline void read(TypeInput& in, uint16_t& value, const TypeCode* type_code, const uint16_t* code) {
	read_value(in, value, type_code, code);
}
inline void read(TypeInput& in, uint32_t& value, const TypeCode* type_code, const uint16_t* code) {
	read_value(in, value, type_code, code);
}
inline void read(TypeInput& in, uint64_t& value, const TypeCode* type_code, const uint16_t* code) {
	read_value(in, value, type_code, code);
}
inline void read(TypeInput& in, char& value, const TypeCode* type_code, const uint16_t* code) {
	read_value(in, value, type_code, code);
}
inline void read(TypeInput& in, int8_t& value, const TypeCode* type_code, const uint16_t* code) {
	read_value(in, value, type_code, code);
}
inline void read(TypeInput& in, int16_t& value, const TypeCode* type_code, const uint16_t* code) {
	read_value(in, value, type_code, code);
}
inline void read(TypeInput& in, int32_t& value, const TypeCode* type_code, const uint16_t* code) {
	read_value(in, value, type_code, code);
}
inline void read(TypeInput& in, int64_t& value, const TypeCode* type_code, const uint16_t* code) {
	read_value(in, value, type_code, code);
}
inline void read(TypeInput& in, float32_t& value, const TypeCode* type_code, const uint16_t* code) {
	read_value(in, value, type_code, code);
}
inline void read(TypeInput& in, float64_t& value, const TypeCode* type_code, const uint16_t* code) {
	read_value(in, value, type_code, code);
}
/// @}

/** \brief Reads a dynamically allocated string from the input stream.
 * 
 * Directly compatible with {CODE_LIST, CODE_INT8}.
 * Indirectly compatible with everything by converting to a string via to_string_value().
 */
void read(TypeInput& in, std::string& string, const TypeCode* type_code, const uint16_t* code);

template<typename T, size_t N>
void read(TypeInput& in, std::array<T, N>& array, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void read(TypeInput& in, std::vector<T>& vector, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void read(TypeInput& in, std::list<T>& list, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void read(TypeInput& in, std::set<T>& set, const TypeCode* type_code, const uint16_t* code);

template<typename T, typename C>
void read(TypeInput& in, std::set<T, C>& set, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void read(TypeInput& in, std::unordered_set<T>& set, const TypeCode* type_code, const uint16_t* code);

template<typename T, typename C>
void read(TypeInput& in, std::unordered_set<T, C>& set, const TypeCode* type_code, const uint16_t* code);

template<typename K, typename V>
void read(TypeInput& in, std::map<K, V>& map, const TypeCode* type_code, const uint16_t* code);

template<typename K, typename V, typename C>
void read(TypeInput& in, std::map<K, V, C>& map, const TypeCode* type_code, const uint16_t* code);

template<typename K, typename V>
void read(TypeInput& in, std::unordered_map<K, V>& map, const TypeCode* type_code, const uint16_t* code);

template<typename K, typename V, typename C>
void read(TypeInput& in, std::unordered_map<K, V, C>& map, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void read(TypeInput& in, std::shared_ptr<T>& value, const TypeCode* type_code, const uint16_t* code);

/**
 * \brief Reads a statically allocated array (ContiguousContainer) from the input stream.
 * 
 * If there is less elements in the data the remaining elements in \p array will be default assigned.
 * Compatible with CODE_ARRAY data. Works for std::array and pre-allocated std::vector.
 */
template<typename T>
void read_array(TypeInput& in, T& array, const TypeCode* type_code, const uint16_t* code) {
	size_t size = 0;
	switch(code[0]) {
		case CODE_ARRAY: size = code[1]; break;
		case CODE_ALT_ARRAY: size = flip_bytes(code[1]); break;
		default: skip(in, type_code, code);
	}
	if(size) {
		const uint16_t* value_code = code + 2;
		if(is_equivalent<typename T::value_type>(value_code[0]) && size <= array.size()) {
			in.read((char*)array.data(), size * sizeof(typename T::value_type));
		} else {
			for(size_t i = 0; i < size; ++i) {
				if(i < array.size()) {
					vnx::type<typename T::value_type>().read(in, array[i], type_code, value_code);
				} else {
					skip(in, type_code, value_code);
				}
			}
		}
	}
	for(size_t i = size; i < array.size(); ++i) {
		array[i] = typename T::value_type();
	}
}

/// Same as read_array<T>() with T = std::array<T, N>
template<typename T, size_t N>
void read(TypeInput& in, std::array<T, N>& array, const TypeCode* type_code, const uint16_t* code) {
	read_array(in, array, type_code, code);
}

/** \brief Reads a dynamically allocated array (ContiguousContainer) from the input stream.
 * 
 * Compatible with CODE_LIST.
 */
template<typename T>
void read_vector(TypeInput& in, T& vector, const TypeCode* type_code, const uint16_t* code) {
	uint32_t size = 0;
	switch(code[0]) {
		case CODE_LIST:
			read(in, size);
			break;
		case CODE_ALT_LIST:
			read(in, size);
			size = flip_bytes(size);
			break;
		default:
			vector.clear();
			skip(in, type_code, code);
			return;
	}
	vector.resize(size);
	const uint16_t* value_code = code + 1;
	if(is_equivalent<typename T::value_type>(value_code[0])) {
		in.read((char*)vector.data(), size * sizeof(typename T::value_type));
	} else {
		for(uint32_t i = 0; i < size; ++i) {
			vnx::type<typename T::value_type>().read(in, vector[i], type_code, value_code);
		}
	}
}

/// Same as read_vector<T>() with T = std::vector<T>
template<typename T>
void read(TypeInput& in, std::vector<T>& vector, const TypeCode* type_code, const uint16_t* code) {
	read_vector(in, vector, type_code, code);
}

/// Same as read_vector<T>() with T = std::vector<T> (specialization for std::vector<bool> fuckup)
template<>
void read(TypeInput& in, std::vector<bool>& vector, const TypeCode* type_code, const uint16_t* code);

/** \brief Reads a dynamically allocated list (SequenceContainer) from the input stream.
 * 
 * Compatible with CODE_LIST.
 */
template<typename T>
void read_list(TypeInput& in, T& list, const TypeCode* type_code, const uint16_t* code) {
	list.clear();
	uint32_t size = 0;
	switch(code[0]) {
		case CODE_LIST:
			read(in, size);
			break;
		case CODE_ALT_LIST:
			read(in, size);
			size = flip_bytes(size);
			break;
		default:
			skip(in, type_code, code);
			return;
	}
	const uint16_t* value_code = code + 1;
	for(uint32_t i = 0; i < size; ++i) {
		list.emplace_back();
		vnx::type<typename T::value_type>().read(in, list.back(), type_code, value_code);
	}
}

/// Same as read_list<T>() with T = std::list<T>
template<typename T>
void read(TypeInput& in, std::list<T>& list, const TypeCode* type_code, const uint16_t* code) {
	read_list(in, list, type_code, code);
}

/** \brief Reads a dynamically allocated set (AssociativeContainer) from the input stream.
 * 
 * Compatible with CODE_LIST.
 */
template<typename T>
void read_set(TypeInput& in, T& set, const TypeCode* type_code, const uint16_t* code) {
	set.clear();
	uint32_t size = 0;
	switch(code[0]) {
		case CODE_LIST:
			read(in, size);
			break;
		case CODE_ALT_LIST:
			read(in, size);
			size = flip_bytes(size);
			break;
		default:
			skip(in, type_code, code);
			return;
	}
	const uint16_t* value_code = code + 1;
	for(uint32_t i = 0; i < size; ++i) {
		typename T::value_type key;
		vnx::type<typename T::value_type>().read(in, key, type_code, value_code);
		set.insert(key);
	}
}

/// Same as read_set<T>() with T = std::set<T>
template<typename T>
void read(TypeInput& in, std::set<T>& set, const TypeCode* type_code, const uint16_t* code) {
	read_set(in, set, type_code, code);
}

/// Same as read_set<T>() with T = std::set<T, C>
template<typename T, typename C>
void read(TypeInput& in, std::set<T, C>& set, const TypeCode* type_code, const uint16_t* code) {
	read_set(in, set, type_code, code);
}

/// Same as read_set<T>() with T = std::unordered_set<T>
template<typename T>
void read(TypeInput& in, std::unordered_set<T>& set, const TypeCode* type_code, const uint16_t* code) {
	read_set(in, set, type_code, code);
}

/// Same as read_set<T>() with T = std::unordered_set<T, C>
template<typename T, typename C>
void read(TypeInput& in, std::unordered_set<T, C>& set, const TypeCode* type_code, const uint16_t* code) {
	read_set(in, set, type_code, code);
}

/** \brief Reads a dynamically allocated map (AssociativeContainer) from the input stream.
 * 
 * Compatible with CODE_MAP.
 */
template<typename T>
void read_map(TypeInput& in, T& map, const TypeCode* type_code, const uint16_t* code) {
	map.clear();
	uint32_t size = 0;
	const uint16_t* key_code = code + 2;
	const uint16_t* value_code = 0;
	switch(code[0]) {
		case CODE_MAP:
			read(in, size);
			value_code = code + code[1];
			break;
		case CODE_ALT_MAP:
			read(in, size);
			size = flip_bytes(size);
			value_code = code + flip_bytes(code[1]);
			break;
		default:
			skip(in, type_code, code);
			return;
	}
	for(size_t i = 0; i < size; ++i) {
		typename T::key_type key;
		vnx::type<typename T::key_type>().read(in, key, type_code, key_code);
		typename T::mapped_type& value = map[key];
		vnx::type<typename T::mapped_type>().read(in, value, type_code, value_code);
	}
}

/// Same as read_map<T>() with T = std::map<K, V>
template<typename K, typename V>
void read(TypeInput& in, std::map<K, V>& map, const TypeCode* type_code, const uint16_t* code) {
	read_map(in, map, type_code, code);
}

/// Same as read_map<T>() with T = std::map<K, V, C>
template<typename K, typename V, typename C>
void read(TypeInput& in, std::map<K, V, C>& map, const TypeCode* type_code, const uint16_t* code) {
	read_map(in, map, type_code, code);
}

/// Same as read_map<T>() with T = std::unordered_map<K, V>
template<typename K, typename V>
void read(TypeInput& in, std::unordered_map<K, V>& map, const TypeCode* type_code, const uint16_t* code) {
	read_map(in, map, type_code, code);
}

/// Same as read_map<T>() with T = std::unordered_map<K, V, C>
template<typename K, typename V, typename C>
void read(TypeInput& in, std::unordered_map<K, V, C>& map, const TypeCode* type_code, const uint16_t* code) {
	read_map(in, map, type_code, code);
}

/** \brief Reads a std::pair from the input stream.
 * 
 * Compatible with CODE_TUPLE.
 */
template<typename K, typename V>
void read(TypeInput& in, std::pair<K, V>& value, const TypeCode* type_code, const uint16_t* code) {
	if((code[0] == CODE_TUPLE && code[1] == 2)
		|| (code[0] == CODE_ALT_TUPLE && flip_bytes(code[1]) == 2))
	{
		vnx::type<K>().read(in, value.first, type_code, code + code[2]);
		vnx::type<V>().read(in, value.second, type_code, code + code[3]);
	} else {
		value = std::pair<K, V>();
		skip(in, type_code, code);
	}
}

/** \brief Reads a statically allocated N-dimensional matrix from the input stream.
 * 
 * The matrix in the data needs to match the exact size requested with \p size,
 * if it does not the output \p data will be default initialized.
 * Compatible with CODE_MATRIX.
 * 
 * @param data Pointer to pre-allocated array of size \p size.
 * @param size Size of the pre-allocated matrix.
 */
template<typename T, size_t N>
void read_matrix(TypeInput& in, T* data, const std::array<size_t, N>& size, const uint16_t* code) {
	size_t total_size = 1;
	for(size_t i = 0; i < N; ++i) {
		total_size *= size[i];
	}
	if((code[0] == CODE_MATRIX && code[1] == N)
		|| (code[0] == CODE_ALT_MATRIX && flip_bytes(code[1]) == N))
	{
		bool is_same = true;
		if(code[0] == CODE_MATRIX) {
			for(size_t i = 0; i < N; ++i) {
				is_same = is_same && code[2 + i] == size[i];
			}
		} else {
			for(size_t i = 0; i < N; ++i) {
				is_same = is_same && flip_bytes(code[2 + i]) == size[i];
			}
		}
		if(is_same) {
			const uint16_t* value_code = code + 2 + N;
			const size_t value_size = get_value_size(value_code[0]);
			if(value_size) {
				if(is_equivalent<T>(value_code[0])) {
					in.read((char*)data, total_size * sizeof(T));
				} else {
					const char* buf = in.read(total_size * value_size);
					for(size_t i = 0; i < total_size; ++i) {
						read_value(buf + i * value_size, data[i], value_code);
					}
				}
			} else {
				for(size_t i = 0; i < total_size; ++i) {
					vnx::type<T>().read(in, data[i], 0, value_code);
				}
			}
			return;
		}
	}
	for(size_t i = 0; i < total_size; ++i) {
		data[i] = T();
	}
	skip(in, 0, code);
}

/** \brief Reads the size of a N-dimensional image from the input stream.
 * 
 * The image in the data needs to match the requested number of dimensions \p N,
 * if it does not a size of all zero is returned.
 * Compatible with CODE_IMAGE.
 * 
 * @param size Size of the image in the following data.
 */
template<size_t N>
void read_image_size(TypeInput& in, std::array<size_t, N>& size, const uint16_t* code) {
	if(	(code[0] == CODE_IMAGE && code[1] == N)
		|| (code[0] == CODE_ALT_IMAGE && flip_bytes(code[1]) == N))
	{
		const char* buf = in.read(4 * N);
		for(size_t i = 0; i < N; ++i) {
			uint32_t size_ = 0;
			read_value(buf + 4 * i, size_);
			if(code[0] == CODE_IMAGE) {
				size[i] = size_;
			} else {
				size[i] = flip_bytes(size_);
			}
		}
	} else {
		for(size_t i = 0; i < N; ++i) {
			size[i] = 0;
		}
	}
}

/** \brief Reads the data of a N-dimensional image from the input stream.
 * 
 * The image in the data needs to match the requested number of dimensions \p N,
 * if it does not the data is skipped and the output \p data is left untouched.
 * Compatible with CODE_IMAGE.
 * 
 * @param data Pointer to pre-allocated array of size \p size.
 * 			Can be a nullptr, in which case the data is skipped.
 * @param size Size of the image previously read by read_image_size().
 */
template<typename T, size_t N>
void read_image_data(TypeInput& in, T* data, const std::array<size_t, N>& size, const uint16_t* code) {
	if(	(code[0] == CODE_IMAGE && code[1] == N)
		|| (code[0] == CODE_ALT_IMAGE && flip_bytes(code[1]) == N))
	{
		size_t total_size = 1;
		for(size_t i = 0; i < N; ++i) {
			total_size *= size[i];
		}
		const uint16_t* value_code = code + 2;
		const size_t value_size = get_value_size(value_code[0]);
		if(data) {
			if(get_value_code<T>() == value_code[0] && sizeof(T) == value_size) {
				in.read((char*)data, total_size * sizeof(T));
			} else {
				for(size_t i = 0; i < total_size; ++i) {
					vnx::type<T>().read(in, data[i], 0, value_code);
				}
			}
		} else {
			if(value_size) {
				copy_bytes(in, 0, total_size * value_size);
			} else {
				for(size_t i = 0; i < total_size; ++i) {
					skip(in, 0, value_code);
				}
			}
		}
	} else {
		skip(in, 0, code);
	}
}

/** \brief Reads a Value from the input stream at top level.
 * 
 * Since this function does not have a \p type_code and \p code argument it assumes that the input stream
 * is at the top level (ie. the beginning of a file or a new socket, implicit CODE_ANY).
 * If the input contains CODE_NULL a nullptr will be returned, otherwise a Value will be returned or an
 * exception is thrown. The function will skip over CODE_PADDING, CODE_ANY, CODE_NONE and CODE_MAGIC.
 * The function will consume any type codes (ie. CODE_TYPE_CODE) encountered until reaching an actual value.
 * 
 * @return The value read from the stream, nullptr in case of CODE_NULL, any derived type in case of CODE_TYPE,
 * 			Object in case of CODE_OBJECT, Generic in case of CODE_DYNAMIC, Struct in case of a struct and
 * 			Binary in case of a non-native (ie. not compiled in or linked in) type.
 */
std::shared_ptr<Value> read(TypeInput& in);

/// Same as read(TypeInput& in) but with a dynamic_pointer_cast on the result.
template<typename T>
void read(TypeInput& in, std::shared_ptr<T>& value) {
	value = std::dynamic_pointer_cast<T>(read(in));
}

/** \brief Reads a Value from the input stream.
 * 
 * Same as read(TypeInput& in) but not at top level, ie. this function expects a code.
 * In case of incompatible data a nullptr will be returned.
 * Compatible with CODE_ANY.
 */
template<typename T>
void read(TypeInput& in, std::shared_ptr<T>& value, const TypeCode* type_code, const uint16_t* code) {
	if(code[0] == CODE_ANY || code[0] == CODE_ALT_ANY) {
		value = std::dynamic_pointer_cast<T>(read(in));
	} else {
		value = 0;
		skip(in, type_code, code);
	}
}

template<typename T>
void type<T>::read(TypeInput& in, T& value, const TypeCode* type_code, const uint16_t* code) {
	vnx::read(in, value, type_code, code);
}

/** \brief Reads a value of type T from the stream.
 * 
 * This function assumes an implicit CODE_DYNAMIC, ie. it expects dynamic code to be in the data.
 * Used primarily by Variant, otherwise in special cases.
 */
template<typename T>
void read_dynamic(TypeInput& in, T& value) {
	uint16_t code[VNX_MAX_BYTE_CODE_SIZE];
	read_byte_code(in, code);
	switch(code[0]) {
		case CODE_DYNAMIC:
		case CODE_ALT_DYNAMIC:
			read_dynamic(in, value);
			break;
		default:
			vnx::type<T>().read(in, value, 0, code);
	}
}

template<typename T>
void read_dynamic_list_size(TypeInput& in, uint16_t* code_, size_t& size_) {
	uint32_t size = 0;
	read_byte_code(in, code_);
	switch(code_[0]) {
		case CODE_LIST: read(in, size); break;
		case CODE_ALT_LIST: read(in, size); size = flip_bytes(size); break;
	}
	size_ = size;
}

template<typename T>
void read_dynamic_list_data(TypeInput& in, T* data_, const uint16_t* code_, const size_t& size_) {
	if((code_[0] == CODE_LIST || code_[0] == CODE_ALT_LIST) && data_) {
		const size_t value_size = get_value_size(code_[1]);
		if(get_value_code<T>() == code_[1] && sizeof(T) == value_size) {
			in.read((char*)data_, size_ * sizeof(T));
		} else {
			const uint16_t* value_code = code_ + 1;
			for(uint32_t i = 0; i < size_; ++i) {
				vnx::type<T>().read(in, data_[i], 0, value_code);
			}
		}
	} else {
		skip(in, 0, code_);
	}
}

template<typename T>
void from_string(const std::string& str, T& value);

template<typename T>
void from_string(const std::string& str, std::shared_ptr<T>& value);

template<typename T>
void from_string(const std::string& str, std::shared_ptr<const T>& value);

/** \brief Copies a value from the JSON stream into \p out.
 * 
 * A value is either a:
 * - number: 123 or 123.456
 * - boolean: true or false (without quotes)
 * - null: null (without quotes)
 * - string: "string with quotes"
 * - array: [1, 2, 3]
 * - object: {"key": 123, "foo": "bar"}
 * 
 * @param in JSON stream to read from
 * @param out Output string to copy into, will be cleared beforehand.
 * @param want_string Can be set to true if a string is expected to follow. If true will also read a string without quotes
 * 			until a JSON delimiter is encountered. Any whitespace is ignored.
 */
bool read_value(std::istream& in, std::string& out, bool want_string = false);

/** \brief Reads an object from the JSON stream.
 * 
 * Example: {"key": 123, "foo": "bar"}
 */
bool read_object(std::istream& in, std::map<std::string, std::string>& object);

/** \brief Reads an object from the JSON string.
 * 
 * Example: {"key": 123, "foo": "bar"}
 */
bool read_object(const std::string& str, std::map<std::string, std::string>& object);

/// Reads a value directly from the JSON stream
/// @{
inline void read(std::istream& in, bool& value) {
	std::string tmp;
	read_value(in, tmp);
	value = !(tmp == "false" || tmp == "null" || tmp == "0");
}
inline void read(std::istream& in, uint8_t& value) { int tmp; in >> tmp; value = uint8_t(tmp); }
inline void read(std::istream& in, uint16_t& value) { in >> value; }
inline void read(std::istream& in, uint32_t& value) { in >> value; }
inline void read(std::istream& in, uint64_t& value) { in >> value; }
inline void read(std::istream& in, char& value) { in >> value; }
inline void read(std::istream& in, int8_t& value) { int tmp; in >> tmp; value = int8_t(tmp); }
inline void read(std::istream& in, int16_t& value) { in >> value; }
inline void read(std::istream& in, int32_t& value) { in >> value; }
inline void read(std::istream& in, int64_t& value) { in >> value; }
inline void read(std::istream& in, float32_t& value) { in >> value; }
inline void read(std::istream& in, float64_t& value) { in >> value; }
/// @}

/** \brief Reads a string from the JSON stream.
 * 
 * Example: "string with whitespace inside double quotes" \n 
 * Example: string_without_quotes_and_no_whitespace
 */
void read(std::istream& in, std::string& value);

/** \brief Reads a JSON value from the input stream.
 * 
 * Depending on the input the returned value (wrapped in a Variant) is either a:
 * - unsigned integer (CODE_UINT64)
 * - signed integer (CODE_INT64)
 * - floating-point value (CODE_DOUBLE)
 * - string (CODE_LIST, CODE_INT8)
 * - array (CODE_LIST)
 * - vnx::Object (CODE_OBJECT)
 */
std::shared_ptr<Variant> read(std::istream& in);

/** \brief Reads a static array from the JSON stream
 * 
 * Example: [1, 2, 3] \n 
 * If the input array is smaller than \p array the left-over elements are default initialized.
 */
template<typename T, size_t N>
void read(std::istream& in, std::array<T, N>& array) {
	size_t stack = 0;
	size_t k = 0;
	while(true) {
		const char c = in.peek();
		if(!in.good()) {
			break;
		}
		if(c == '[') {
			stack++;
			in.get();
		} else if(c == ']') {
			in.get();
			break;
		} else if(stack && c != ',') {
			std::string value;
			if(!read_value(in, value)) {
				break;		// prevent infinite loop
			}
			if(k < N) {
				from_string(value, array[k++]);
			}
		} else {
			in.get();
		}
	}
	for(size_t i = k; i < N; ++i) {
		array[i] = T();
	}
}

/** \brief Reads a dynamic array from the JSON stream
 * 
 * Example: [1, 2, 3]
 */
template<typename T>
void read(std::istream& in, std::vector<T>& vector) {
	vector.clear();
	int stack = 0;
	while(true) {
		const char c = in.peek();
		if(!in.good()) {
			break;
		}
		if(!stack && c == '[') {
			stack++;
			in.get();
		} else if(stack && c == ']') {
			in.get();
			break;
		} else if(c != ',' && c != ' ') {
			std::string value;
			if(!read_value(in, value)) {
				break;		// prevent infinite loop
			}
			T next = T();
			from_string(value, next);
			vector.push_back(next);
		} else {
			in.get();
		}
	}
}

/** \brief Reads a pair from the JSON stream
 * 
 * Example: ["key", "value"] \n 
 * Example: {"key": "value"}
 */
template<typename K, typename V>
void read(std::istream& in, std::pair<K, V>& pair) {
	pair = std::pair<K, V>();
	int stack = 0;
	int state = 0;
	while(true) {
		const char c = in.peek();
		if(!in.good()) {
			break;
		}
		if(c == '[' || c == '{') {
			in.get();
			stack++;
		} else if(c == ']' || c == '}') {
			in.get();
			break;
		} else if(c == ',' || c == ':') {
			in.get();
			stack++;
		} else if(stack > state) {
			std::string value;
			if(!read_value(in, value)) {
				break;		// prevent infinite loop
			}
			if(stack == 1) {
				from_string(value, pair.first);
				state++;
			} else if(stack == 2) {
				from_string(value, pair.second);
				state++;
			}
		} else {
			in.get();
		}
	}
}

/** \brief Reads a map from the JSON stream
 * 
 * Example: [[1, 1.234], [123, 5.678]] \n 
 * Example: {"foo": 1, "bar": 123}
 */
template<typename K, typename V>
void read(std::istream& in, std::map<K, V>& map) {
	map.clear();
	int stack = 0;
	while(true) {
		const char c = in.peek();
		if(!in.good()) {
			break;
		}
		if(!stack && c == '{') {
			std::map<std::string, std::string> object;
			read_object(in, object);
			for(const auto& entry : object) {
				K key = K();
				from_string(entry.first, key);
				from_string(entry.second, map[key]);
			}
			break;
		} else if(c == '[') {
			if(stack) {
				std::pair<K, V> entry;
				read(in, entry);
				map[entry.first] = entry.second;
			} else {
				in.get();
				stack++;
			}
		} else if(c == ']') {
			in.get();
			break;
		} else {
			in.get();
		}
	}
}

/** \brief Reads a matrix from the JSON stream.
 * 
 * Example: [1, 2, 3, 4]	// column vector \n 
 * Example: {"size": [2, 2], "data": [1, 2, 3, 4]}		// general N-by-M matrix \n 
 */
template<typename T, size_t N>
void read_matrix(std::istream& in, T* data, const std::array<size_t, N>& size) {
	size_t total_size = 1;
	for(size_t i = 0; i < N; ++i) {
		total_size *= size[i];
	}
	std::string str;
	read(in, str);
	std::vector<T> tmp;
	if(!str.empty()) {
		if(str[0] == '[') {
			from_string(str, tmp);
		} else if(str[0] == '{') {
			std::map<std::string, std::string> object;
			read_object(str, object);
			from_string(object["data"], tmp);
		}
	}
	for(size_t i = 0; i < total_size; ++i) {
		if(i < tmp.size()) {
			data[i] = tmp[i];
		} else {
			data[i] = T();
		}
	}
}

template<size_t N>
void read_image_size(std::istream& in, std::array<size_t, N>& size) {
	// not implemented yet
	for(size_t i = 0; i < N; ++i) {
		size[i] = 0;
	}
}

template<typename T, size_t N>
void read_image_data(std::istream& in, T* data, const std::array<size_t, N>& size) {
	// not implemented yet
}

template<typename T>
void type<T>::read(std::istream& in, T& value) {
	vnx::read(in, value);
}

/// Reads a value of type T from the JSON string
template<typename T>
void from_string(const std::string& str, T& value) {
	std::istringstream stream;
	stream.str(str);
	vnx::type<T>().read(stream, value);
}

/// Reads a Value of type T from the JSON stream
template<typename T>
void from_string(const std::string& str, std::shared_ptr<T>& value) {
	if(!value) {
		value = T::create();
	}
	if(value) {
		std::istringstream stream;
		stream.str(str);
		value->read(stream);
	}
}

/// Reads a Value of type T from the JSON stream
template<typename T>
void from_string(const std::string& str, std::shared_ptr<const T>& value) {
	std::shared_ptr<T> tmp = T::create();
	if(tmp) {
		std::istringstream stream;
		stream.str(str);
		tmp->read(stream);
	}
	value = tmp;
}

/// Reads a TypeCode from the stream
void read_type_code(TypeInput& in);

/** \brief Reads a value from the file given by \p file_name.
 * 
 * Will read the first value in the file in case of multiple values.
 * 
 * @return Returns null in case of failure, returns a Binary in case the value type is not naive,
 * 			otherwise returns the actual value.
 */
std::shared_ptr<Value> read_from_file(const std::string& file_name);

/// Same as read_from_file() but will try to dynamic cast to T
template<typename T>
std::shared_ptr<T> read_from_file(const std::string& file_name) {
	return std::dynamic_pointer_cast<T>(read_from_file(file_name));
}


} // vnx

#endif /* INCLUDE_VNX_INPUT_H_ */

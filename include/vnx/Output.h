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

#ifndef INCLUDE_VNX_OUTPUT_H_
#define INCLUDE_VNX_OUTPUT_H_

#include <vnx/Type.h>
#include <vnx/OutputStream.h>

#include <sstream>


namespace vnx {

/// Directly writes a value to the buffer address \p buf.
/// @{
inline void write_value(void* buf, const bool& value) {
	*((uint8_t*)buf) = uint8_t(value);
}
inline void write_value(void* buf, const uint8_t& value) {
	*((uint8_t*)buf) = value;
}
inline void write_value(void* buf, const uint16_t& value) {
	*((uint16_t*)buf) = value;
}
inline void write_value(void* buf, const uint32_t& value) {
	*((uint32_t*)buf) = value;
}
inline void write_value(void* buf, const uint64_t& value) {
	*((uint64_t*)buf) = value;
}
inline void write_value(void* buf, const char& value) {
	*((int8_t*)buf) = int8_t(value);
}
inline void write_value(void* buf, const int8_t& value) {
	*((int8_t*)buf) = value;
}
inline void write_value(void* buf, const int16_t& value) {
	*((int16_t*)buf) = value;
}
inline void write_value(void* buf, const int32_t& value) {
	*((int32_t*)buf) = value;
}
inline void write_value(void* buf, const int64_t& value) {
	*((int64_t*)buf) = value;
}
inline void write_value(void* buf, const float32_t& value) {
	*((float32_t*)buf) = value;
}
inline void write_value(void* buf, const float64_t& value) {
	*((float64_t*)buf) = value;
}
/// @}

/// Directly writes a static array to the buffer address \p buf.
template<typename T, size_t N>
inline void write_value(char* buf, const std::array<T, N>& array) {
	for(size_t i = 0; i < N; ++i) {
		write_value(buf + i * sizeof(T), array[i]);
	}
}

/// Directly writes a value to the stream.
/// @{
inline void write(TypeOutput& out, const bool& value, const TypeCode* type_code = 0, const uint16_t* code = 0) {
	*((uint8_t*)out.write(sizeof(uint8_t))) = uint8_t(value);
}
inline void write(TypeOutput& out, const uint8_t& value, const TypeCode* type_code = 0, const uint16_t* code = 0) {
	*((uint8_t*)out.write(sizeof(uint8_t))) = value;
}
inline void write(TypeOutput& out, const uint16_t& value, const TypeCode* type_code = 0, const uint16_t* code = 0) {
	*((uint16_t*)out.write(sizeof(uint16_t))) = value;
}
inline void write(TypeOutput& out, const uint32_t& value, const TypeCode* type_code = 0, const uint16_t* code = 0) {
	*((uint32_t*)out.write(sizeof(uint32_t))) = value;
}
inline void write(TypeOutput& out, const uint64_t& value, const TypeCode* type_code = 0, const uint16_t* code = 0) {
	*((uint64_t*)out.write(sizeof(uint64_t))) = value;
}
inline void write(TypeOutput& out, const char& value, const TypeCode* type_code = 0, const uint16_t* code = 0) {
	*((int8_t*)out.write(sizeof(int8_t))) = int8_t(value);
}
inline void write(TypeOutput& out, const int8_t& value, const TypeCode* type_code = 0, const uint16_t* code = 0) {
	*((int8_t*)out.write(sizeof(int8_t))) = value;
}
inline void write(TypeOutput& out, const int16_t& value, const TypeCode* type_code = 0, const uint16_t* code = 0) {
	*((int16_t*)out.write(sizeof(int16_t))) = value;
}
inline void write(TypeOutput& out, const int32_t& value, const TypeCode* type_code = 0, const uint16_t* code = 0) {
	*((int32_t*)out.write(sizeof(int32_t))) = value;
}
inline void write(TypeOutput& out, const int64_t& value, const TypeCode* type_code = 0, const uint16_t* code = 0) {
	*((int64_t*)out.write(sizeof(int64_t))) = value;
}
inline void write(TypeOutput& out, const float32_t& value, const TypeCode* type_code = 0, const uint16_t* code = 0) {
	*((float32_t*)out.write(sizeof(float32_t))) = value;
}
inline void write(TypeOutput& out, const float64_t& value, const TypeCode* type_code = 0, const uint16_t* code = 0) {
	*((float64_t*)out.write(sizeof(float64_t))) = value;
}
/// @}

/// Writes a value dynamically to the stream.
/// @{
void write_dynamic(TypeOutput& out, const bool& value);
void write_dynamic(TypeOutput& out, const uint8_t& value);
void write_dynamic(TypeOutput& out, const uint16_t& value);
void write_dynamic(TypeOutput& out, const uint32_t& value);
void write_dynamic(TypeOutput& out, const uint64_t& value);
void write_dynamic(TypeOutput& out, const char& value);
void write_dynamic(TypeOutput& out, const int8_t& value);
void write_dynamic(TypeOutput& out, const int16_t& value);
void write_dynamic(TypeOutput& out, const int32_t& value);
void write_dynamic(TypeOutput& out, const int64_t& value);
void write_dynamic(TypeOutput& out, const float32_t& value);
void write_dynamic(TypeOutput& out, const float64_t& value);
/// @}

/// Writes CODE_NULL to the stream
inline void write_null(TypeOutput& out) {
	write(out, uint16_t(CODE_NULL));
}

/// Writes CODE_NULL dynamically to the stream
void write_dynamic_null(TypeOutput& out);

/** \brief Writes \p size number of bytes of padding to the stream.
 * 
 * Includes CODE_PADDING and size information, thus the minimum padding size is 6 bytes.
 */
void write_padding(TypeOutput& out, size_t size);

/// Writes the given byte code to the stream.
void write_byte_code(TypeOutput& out, const uint16_t* code);

/// Writes the given byte code to the stream
void write_byte_code(TypeOutput& out, const uint16_t* code, size_t code_size);

void write(TypeOutput& out, const std::string& string, const TypeCode* type_code, const uint16_t* code);

template<typename T, size_t N>
void write(TypeOutput& out, const std::array<T, N>& array, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void write(TypeOutput& out, const std::vector<T>& vector, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void write(TypeOutput& out, const std::list<T>& list, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void write(TypeOutput& out, const std::set<T>& set, const TypeCode* type_code, const uint16_t* code);

template<typename T, typename C>
void write(TypeOutput& out, const std::set<T, C>& set, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void write(TypeOutput& out, const std::unordered_set<T>& set, const TypeCode* type_code, const uint16_t* code);

template<typename T, typename C>
void write(TypeOutput& out, const std::unordered_set<T, C>& set, const TypeCode* type_code, const uint16_t* code);

template<typename K, typename V>
void write(TypeOutput& out, const std::map<K, V>& map, const TypeCode* type_code, const uint16_t* code);

template<typename K, typename V, typename C>
void write(TypeOutput& out, const std::map<K, V, C>& map, const TypeCode* type_code, const uint16_t* code);

template<typename K, typename V>
void write(TypeOutput& out, const std::unordered_map<K, V>& map, const TypeCode* type_code, const uint16_t* code);

template<typename K, typename V, typename C>
void write(TypeOutput& out, const std::unordered_map<K, V, C>& map, const TypeCode* type_code, const uint16_t* code);

void write(TypeOutput& out, const Value& value, const TypeCode* type_code, const uint16_t* code);

void write(TypeOutput& out, const std::nullptr_t& value, const TypeCode* type_code, const uint16_t* code);

void write(TypeOutput& out, std::shared_ptr<const Value> value, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void write(TypeOutput& out, std::shared_ptr<T> value, const TypeCode* type_code, const uint16_t* code);

void write(TypeOutput& out, const Value& value);

void write(TypeOutput& out, const Variant& value);

void write(TypeOutput& out, const std::nullptr_t& value);

void write(TypeOutput& out, std::shared_ptr<const Value> value);

template<typename T>
void write(TypeOutput& out, std::shared_ptr<T> value);

/// Writes a static array (ContiguousContainer) to the stream
template<typename T>
void write_array(TypeOutput& out, const T& array, const TypeCode* type_code, const uint16_t* code) {
	if(array.size() > VNX_MAX_STATIC_SIZE) {
		throw std::invalid_argument("write_array(): size > VNX_MAX_STATIC_SIZE");
	}
	for(const auto& elem : array) {
		vnx::type<typename T::value_type>().write(out, elem, type_code, code);
	}
}

template<typename T, size_t N>
void write(TypeOutput& out, const std::array<T, N>& array, const TypeCode* type_code, const uint16_t* code) {
	write_array(out, array, type_code, code);
}

/// Writes a dynamic vector (ContiguousContainer) to the stream
template<typename T>
void write_vector(TypeOutput& out, const T& vector, const TypeCode* type_code, const uint16_t* code) {
	if(vector.size() > VNX_MAX_SIZE) {
		throw std::invalid_argument("write_vector(): size > VNX_MAX_SIZE");
	}
	write(out, (uint32_t)vector.size());
	if(sizeof(typename T::value_type) == get_value_size(get_value_code<typename T::value_type>())) {
		out.write(vector.data(), vector.size() * sizeof(typename T::value_type));
	} else {
		const uint16_t* value_code = code ? code + 1 : 0;
		for(const auto& elem : vector) {
			vnx::type<typename T::value_type>().write(out, elem, type_code, value_code);
		}
	}
}

template<typename T>
void write(TypeOutput& out, const std::vector<T>& vector, const TypeCode* type_code, const uint16_t* code) {
	write_vector(out, vector, type_code, code);
}

template<>
void write(TypeOutput& out, const std::vector<bool>& vector, const TypeCode* type_code, const uint16_t* code);

/// Writes a dynamic list (SequenceContainer) to the stream
template<typename T>
void write_list(TypeOutput& out, const T& list, const TypeCode* type_code, const uint16_t* code) {
	if(list.size() > VNX_MAX_SIZE) {
		throw std::invalid_argument("write_list(): size > VNX_MAX_SIZE");
	}
	write(out, (uint32_t)list.size());
	const uint16_t* value_code = code ? code + 1 : 0;
	for(const auto& elem : list) {
		vnx::type<typename T::value_type>().write(out, elem, type_code, value_code);
	}
}

template<typename T>
void write(TypeOutput& out, const std::list<T>& list, const TypeCode* type_code, const uint16_t* code) {
	write_list(out, list, type_code, code);
}

template<typename T>
void write(TypeOutput& out, const std::set<T>& set, const TypeCode* type_code, const uint16_t* code) {
	write_list(out, set, type_code, code);
}

template<typename T, typename C>
void write(TypeOutput& out, const std::set<T, C>& set, const TypeCode* type_code, const uint16_t* code) {
	write_list(out, set, type_code, code);
}

template<typename T>
void write(TypeOutput& out, const std::unordered_set<T>& set, const TypeCode* type_code, const uint16_t* code) {
	write_list(out, set, type_code, code);
}

template<typename T, typename C>
void write(TypeOutput& out, const std::unordered_set<T, C>& set, const TypeCode* type_code, const uint16_t* code) {
	write_list(out, set, type_code, code);
}

/// Writes a dynamic map (AssociativeContainer) to the stream
template<typename T>
void write_map(TypeOutput& out, const T& map, const TypeCode* type_code, const uint16_t* code) {
	if(map.size() > VNX_MAX_SIZE) {
		throw std::invalid_argument("write_map(): size > VNX_MAX_SIZE");
	}
	write(out, (uint32_t)map.size());
	const uint16_t* key_code = code ? code + 2 : 0;
	const uint16_t* value_code = code ? code + code[1] : 0;
	for(const auto& elem : map) {
		vnx::type<typename T::key_type>().write(out, elem.first, type_code, key_code);
		vnx::type<typename T::mapped_type>().write(out, elem.second, type_code, value_code);
	}
}

template<typename K, typename V>
void write(TypeOutput& out, const std::map<K, V>& map, const TypeCode* type_code, const uint16_t* code) {
	write_map(out, map, type_code, code);
}

template<typename K, typename V, typename C>
void write(TypeOutput& out, const std::map<K, V, C>& map, const TypeCode* type_code, const uint16_t* code) {
	write_map(out, map, type_code, code);
}

template<typename K, typename V>
void write(TypeOutput& out, const std::unordered_map<K, V>& map, const TypeCode* type_code, const uint16_t* code) {
	write_map(out, map, type_code, code);
}

template<typename K, typename V, typename C>
void write(TypeOutput& out, const std::unordered_map<K, V, C>& map, const TypeCode* type_code, const uint16_t* code) {
	write_map(out, map, type_code, code);
}

template<typename K, typename V>
void write(TypeOutput& out, const std::pair<K, V>& value, const TypeCode* type_code, const uint16_t* code) {
	vnx::type<K>().write(out, value.first, type_code, code ? code + code[2] : 0);
	vnx::type<V>().write(out, value.second, type_code, code ? code + code[3] : 0);
}

/// Writes a plain array dynamically (ContiguousContainer) to the stream using CODE_LIST
template<typename T>
void write_dynamic_list(TypeOutput& out, const T* data, const size_t size) {
	if(size > VNX_MAX_SIZE) {
		throw std::invalid_argument("write_dynamic_list(): size > VNX_MAX_SIZE");
	}
	std::vector<uint16_t> code;
	code.push_back(CODE_LIST);
	vnx::type<T>().create_dynamic_code(code);
	write_byte_code(out, code.data(), code.size());
	write(out, (uint32_t)size);
	const uint16_t* value_code = &code[1];
	if(sizeof(T) == get_value_size(value_code[0])) {
		out.write(data, size * sizeof(T));
	} else {
		for(size_t i = 0; i < size; ++i) {
			write(out, data[i], nullptr, value_code);
		}
	}
}

/** \brief Writes a value dynamically to the stream.
 * 
 * Assumes CODE_DYNAMIC.
 * For top level writing CODE_DYNAMIC needs to be written first.
 */
template<typename T>
void write_dynamic(TypeOutput& out, const T& value) {
	std::vector<uint16_t> code;
	vnx::type<T>().create_dynamic_code(code, value, true);
	if(code.empty()) {
		throw std::logic_error("code.empty()");
	}
	write_byte_code(out, code.data(), code.size());
	if(code[0] != CODE_NULL) {
		vnx::type<T>().write(out, value, nullptr, code.data());
	}
}

/** \brief Writes a matrix to the stream
 * 
 * @param data Pointer to array of elements
 * @param size Dimensionality of the matrix
 * @param code Matrix type code
 */
template<typename T, size_t N>
void write_matrix(TypeOutput& out, const T* data, const std::array<size_t, N>& size, const uint16_t* code) {
	size_t total_size = 1;
	for(size_t i = 0; i < N; ++i) {
		total_size *= size[i];
		if(size[i] > VNX_MAX_STATIC_SIZE) {
			throw std::invalid_argument("write_matrix(): size[" + std::to_string(i) + "] > VNX_MAX_STATIC_SIZE");
		}
	}
	if(sizeof(T) == get_value_size(get_value_code<T>())) {
		out.write(data, total_size * sizeof(T));
	} else {
		for(size_t i = 0; i < total_size; ++i) {
			vnx::type<T>().write(out, data[i], nullptr, code);
		}
	}
}

/** \brief Writes an image to the stream
 * 
 * @param data Pointer to array of pixels
 * @param size Dimensionality of the image
 * @param code Image type code
 */
template<typename T, size_t N>
void write_image(TypeOutput& out, const T* data, const std::array<size_t, N>& size, const uint16_t* code) {
	if(code[1] != N) {
		throw std::logic_error("write_image(): code[1] != N");
	}
	size_t total_size = 1;
	for(size_t i = 0; i < N; ++i) {
		total_size *= size[i];
		if(size[i] > VNX_MAX_SIZE) {
			throw std::invalid_argument("write_image(): size[" + std::to_string(i) + "] > VNX_MAX_SIZE");
		}
	}
	char* buf = out.write(4 * N);
	for(size_t i = 0; i < N; ++i) {
		write_value(buf + 4 * i, (uint32_t)size[i]);
	}
	if(sizeof(T) == get_value_size(get_value_code<T>())) {
		out.write(data, total_size * sizeof(T));
	} else {
		for(size_t i = 0; i < total_size; ++i) {
			vnx::type<T>().write(out, data[i], nullptr, code);
		}
	}
}

template<typename T>
void write(TypeOutput& out, std::shared_ptr<T> value) {
	write(out, value, nullptr, nullptr);
}

template<typename T>
void write(TypeOutput& out, std::shared_ptr<T> value, const TypeCode* type_code, const uint16_t* code) {
	write(out, std::dynamic_pointer_cast<const Value>(value), type_code, code);
}

template<typename T>
void type<T>::write(TypeOutput& out, const T& value, const TypeCode* type_code, const uint16_t* code) {
	vnx::write(out, value, type_code, code);
}


inline void write(std::ostream& out, const bool& value) { out << (value ? "true" : "false"); }
inline void write(std::ostream& out, const uint8_t& value) { out << int(value); }
inline void write(std::ostream& out, const uint16_t& value) { out << value; }
inline void write(std::ostream& out, const uint32_t& value) { out << value; }
inline void write(std::ostream& out, const uint64_t& value) { out << value; }
inline void write(std::ostream& out, const char& value) { out << value; }
inline void write(std::ostream& out, const int8_t& value) { out << int(value); }
inline void write(std::ostream& out, const int16_t& value) { out << value; }
inline void write(std::ostream& out, const int32_t& value) { out << value; }
inline void write(std::ostream& out, const int64_t& value) { out << value; }
inline void write(std::ostream& out, const float32_t& value) { out << value; }
inline void write(std::ostream& out, const float64_t& value) { out << value; }

void write(std::ostream& out, const std::string& value);

void write(std::ostream& out, const vnx::Value& value);

template<typename T>
void write(std::ostream& out, std::shared_ptr<T> value);

template<class Iter>
void write_sequence(std::ostream& out, Iter first, Iter last);

template<typename K, typename V>
void write(std::ostream& out, const std::pair<K, V>& value);

template<typename T, size_t N>
void write(std::ostream& out, const std::array<T, N>& array);

template<typename T>
void write(std::ostream& out, const std::vector<T>& vector);

template<typename T>
void write(std::ostream& out, const std::list<T>& list);

template<typename T, size_t N>
void write(std::ostream& out, const std::array<T, N>& array) {
	out << '[';
	for(size_t i = 0; i < N; ++i) {
		if(i > 0) {
			out << ", ";
		}
		vnx::type<T>().write(out, array[i]);
	}
	out << ']';
}

template<typename T>
void write(std::ostream& out, const std::vector<T>& vector) {
	write_sequence(out, vector.begin(), vector.end());
}

template<typename T>
void write(std::ostream& out, const std::list<T>& list) {
	write_sequence(out, list.begin(), list.end());
}

template<>
void write(std::ostream& out, const std::vector<bool>& vector);

template<typename K, typename V>
void write(std::ostream& out, const std::pair<K, V>& value) {
	out << '[';
	vnx::type<K>().write(out, value.first);
	out << ", ";
	vnx::type<V>().write(out, value.second);
	out << ']';
}

template<typename T>
void write(std::ostream& out, const std::set<T>& set) {
	write_sequence(out, set.begin(), set.end());
}

template<typename K, typename V>
void write(std::ostream& out, const std::map<K, V>& map) {
	write_sequence(out, map.begin(), map.end());
}

template<class Iter>
void write_sequence(std::ostream& out, Iter first, Iter last) {
	out << '[';
	for(Iter it = first; it != last; ++it) {
		if(it != first) {
			out << ", ";
		}
		vnx::type<typename Iter::value_type>().write(out, *it);
	}
	out << ']';
}

template<typename T>
void write(std::ostream& out, std::shared_ptr<T> value) {
	if(value) {
		value->write(out);
	} else {
		out << "null";
	}
}

template<typename T>
void write_list(std::ostream& out, const T* data, const size_t size) {
	out << '[';
	for(size_t i = 0; i < size; ++i) {
		if(i > 0) {
			out << ", ";
		}
		vnx::type<T>().write(out, data[i]);
	}
	out << ']';
}

template<typename T, size_t N>
void write_matrix(std::ostream& out, const T* data, const std::array<size_t, N>& size) {
	size_t total_size = 1;
	bool is_array = true;
	for(size_t i = 0; i < N; ++i) {
		total_size *= size[i];
		if(i > 0 && size[i] != 1) {
			is_array = false;
		}
	}
	if(is_array) {
		write_list(out, data, total_size);
	} else {
		out << "{\"size\": ";
		write(out, size);
		out << ", \"data\": ";
		write_list(out, data, total_size);
		out << "}";
	}
}

template<typename T, size_t N>
void write_image(std::ostream& out, const T* data, const std::array<size_t, N>& size) {
	write_matrix(out, data, size);
}

template<typename T>
void type<T>::write(std::ostream& out, const T& value) {
	vnx::write(out, value);
}

/// Converts value to JSON string
template<typename T>
std::string to_string(const T& value) {
	std::ostringstream stream;
	vnx::type<T>().write(stream, value);
	return stream.str();
}

/// Converts value to JSON string
inline std::string to_string(const char* value) {
	return to_string(std::string(value));
}

/// Converts binary value to JSON string
std::string to_string(TypeInput& in);

/// Converts binary value to JSON string
std::string to_string(TypeInput& in, const TypeCode* type_code, const uint16_t* code);

/// Converts binary value to regular string (same as to_string_value<T>())
std::string to_string_value(TypeInput& in);

/// Converts binary value to regular string (same as to_string_value<T>())
std::string to_string_value(TypeInput& in, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void write_class_header(TypeOutput& out) {
	char* const buf = out.write(10);
	write_value(buf, uint16_t(CODE_TYPE));
	write_value(buf + 2, uint64_t(T::VNX_CODE_HASH));
}

void write_class_header(TypeOutput& out, const TypeCode* type_code);

/// Writes the given value to file in binary format
void write_to_file(const std::string& file_name, const Value& value);

/// Writes the given value to file in binary format
void write_to_file(const std::string& file_name, std::shared_ptr<const Value> value);

template<typename T>
void write_to_file_json(const std::string& file_name, const T& value);


} // vnx

#endif /* INCLUDE_VNX_OUTPUT_H_ */

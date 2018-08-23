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

#include <vnx/OutputStream.h>

#include <sstream>


namespace vnx {

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

template<typename T, size_t N>
inline void write_value(char* buf, const std::array<T, N>& array) {
	for(size_t i = 0; i < N; ++i) {
		write_value(buf + i * sizeof(T), array[i]);
	}
}

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

void write_dynamic(TypeOutput& out, const bool& value);
void write_dynamic(TypeOutput& out, const uint8_t& value);
void write_dynamic(TypeOutput& out, const uint16_t& value);
void write_dynamic(TypeOutput& out, const uint32_t& value);
void write_dynamic(TypeOutput& out, const uint64_t& value);
void write_dynamic(TypeOutput& out, const int8_t& value);
void write_dynamic(TypeOutput& out, const int16_t& value);
void write_dynamic(TypeOutput& out, const int32_t& value);
void write_dynamic(TypeOutput& out, const int64_t& value);
void write_dynamic(TypeOutput& out, const float32_t& value);
void write_dynamic(TypeOutput& out, const float64_t& value);

inline void write_null(TypeOutput& out) {
	write(out, uint16_t(CODE_NULL));
}

void write_dynamic_null(TypeOutput& out);

void write_padding(TypeOutput& out, size_t size);

void write_byte_code(TypeOutput& out, const uint16_t* code);

void write_byte_code(TypeOutput& out, const uint16_t* code, size_t code_size);

void write(TypeOutput& out, const std::string& string, const TypeCode* type_code, const uint16_t* code);

template<typename T, size_t N>
void write(TypeOutput& out, const std::array<T, N>& array, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void write(TypeOutput& out, const std::vector<T>& vector, const TypeCode* type_code, const uint16_t* code);

template<typename K, typename V>
void write(TypeOutput& out, const std::map<K, V>& map, const TypeCode* type_code, const uint16_t* code);

void write(TypeOutput& out, const Value& value, const TypeCode* type_code, const uint16_t* code);

void write(TypeOutput& out, std::shared_ptr<const Value> value, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void write(TypeOutput& out, std::shared_ptr<T> value, const TypeCode* type_code, const uint16_t* code);

void write(TypeOutput& out, const Value& value);

void write(TypeOutput& out, std::shared_ptr<const Value> value);

template<typename T>
void write(TypeOutput& out, std::shared_ptr<T> value);

void write_dynamic(TypeOutput& out, const std::string& string);

template<typename T, size_t N>
void write(TypeOutput& out, const std::array<T, N>& array, const TypeCode* type_code, const uint16_t* code) {
	for(size_t i = 0; i < N; ++i) {
		vnx::type<T>().write(out, array[i], type_code, code);
	}
}

template<typename T>
void write(TypeOutput& out, const std::vector<T>& vector, const TypeCode* type_code, const uint16_t* code) {
	if(vector.size() > VNX_MAX_SIZE) {
		throw std::invalid_argument("write(std::vector<T>): size > VNX_MAX_SIZE");
	}
	write(out, (uint32_t)vector.size());
	if(sizeof(T) == get_value_size(get_value_code<T>())) {
		out.write(vector.data(), vector.size() * sizeof(T));
	} else {
		const uint16_t* value_code = code ? code + 1 : 0;
		for(const T& elem : vector) {
			vnx::type<T>().write(out, elem, type_code, value_code);
		}
	}
}

template<typename K, typename V>
void write(TypeOutput& out, const std::map<K, V>& map, const TypeCode* type_code, const uint16_t* code) {
	if(map.size() > VNX_MAX_SIZE) {
		throw std::invalid_argument("write(std::map<K, V>): size > VNX_MAX_SIZE");
	}
	write(out, (uint32_t)map.size());
	const uint16_t* key_code = code ? code + 2 : 0;
	const uint16_t* value_code = code ? code + code[1] : 0;
	for(const std::pair<K, V>& elem : map) {
		vnx::type<K>().write(out, elem.first, type_code, key_code);
		vnx::type<V>().write(out, elem.second, type_code, value_code);
	}
}

template<typename K, typename V>
void write(TypeOutput& out, const std::pair<K, V>& value, const TypeCode* type_code, const uint16_t* code) {
	vnx::type<K>().write(out, value.first, type_code, code ? code + code[2] : 0);
	vnx::type<V>().write(out, value.second, type_code, code ? code + code[3] : 0);
}

template<typename T>
void write_dynamic_list(TypeOutput& out, const T* data, const size_t size) {
	if(size > VNX_MAX_SIZE) {
		throw std::invalid_argument("write_dynamic_list(T*): size > VNX_MAX_SIZE");
	}
	std::vector<uint16_t> code;
	vnx::type<std::vector<T>>().create_dynamic_code(code);
	write_byte_code(out, code.data(), code.size());
	write(out, (uint32_t)size);
	if(sizeof(T) == get_value_size(get_value_code<T>())) {
		out.write(data, size * sizeof(T));
	} else {
		for(size_t i = 0; i < size; ++i) {
			write(out, data[i], 0, code.data());
		}
	}
}

template<typename T>
void write_dynamic(TypeOutput& out, const T& value) {
	std::vector<uint16_t> code;
	vnx::type<T>().create_dynamic_code(code);
	write_byte_code(out, code.data(), code.size());
	vnx::type<T>().write(out, value, 0, code.data());
}

template<typename T, size_t N>
void write_matrix(TypeOutput& out, const T* data, const std::array<size_t, N>& size, const uint16_t* code) {
	size_t total_size = 1;
	for(size_t i = 0; i < N; ++i) {
		total_size *= size[i];
		if(size[i] > VNX_MAX_STATIC_SIZE) {
			throw std::invalid_argument("write_matrix(T*): size[" + std::to_string(i) + "] > VNX_MAX_STATIC_SIZE");
		}
	}
	if(sizeof(T) == get_value_size(get_value_code<T>())) {
		out.write(data, total_size * sizeof(T));
	} else {
		for(size_t i = 0; i < total_size; ++i) {
			vnx::type<T>().write(out, data[i], 0, code);
		}
	}
}

template<typename T, size_t N>
void write_image(TypeOutput& out, const T* data, const std::array<size_t, N>& size, const uint16_t* code) {
	size_t total_size = 1;
	for(size_t i = 0; i < N; ++i) {
		total_size *= size[i];
		if(size[i] > VNX_MAX_SIZE) {
			throw std::invalid_argument("write_image(T*): size[" + std::to_string(i) + "] > VNX_MAX_SIZE");
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
			vnx::type<T>().write(out, data[i], 0, code);
		}
	}
}

template<typename T>
void write(TypeOutput& out, std::shared_ptr<T> value) {
	write(out, value, 0, 0);
}

template<typename T>
void write(TypeOutput& out, std::shared_ptr<T> value, const TypeCode* type_code, const uint16_t* code) {
	write(out, std::dynamic_pointer_cast<const Value>(value), type_code, code);
}

template<typename T>
void type<T>::write(TypeOutput& out, const T& value, const TypeCode* type_code, const uint16_t* code) {
	vnx::write(out, value, type_code, code);
}


inline void write(std::ostream& out, const bool& value) { out << int(value); }
inline void write(std::ostream& out, const uint8_t& value) { out << int(value); }
inline void write(std::ostream& out, const uint16_t& value) { out << value; }
inline void write(std::ostream& out, const uint32_t& value) { out << value; }
inline void write(std::ostream& out, const uint64_t& value) { out << value; }
inline void write(std::ostream& out, const int8_t& value) { out << int(value); }
inline void write(std::ostream& out, const int16_t& value) { out << value; }
inline void write(std::ostream& out, const int32_t& value) { out << value; }
inline void write(std::ostream& out, const int64_t& value) { out << value; }

inline void write(std::ostream& out, const float32_t& value) {
	char buf[128];
	snprintf(buf, sizeof(buf), "%.*f", 4, value);
	out << std::string(buf);
}

inline void write(std::ostream& out, const float64_t& value) {
	char buf[128];
	snprintf(buf, sizeof(buf), "%.*f", 8, value);
	out << std::string(buf);
}

void write(std::ostream& out, const std::string& value);

template<typename T>
void write(std::ostream& out, std::shared_ptr<T> value);

template<class Iter>
void write_list(std::ostream& out, Iter first, Iter last);

template<typename K, typename V>
void write(std::ostream& out, const std::pair<K, V>& value);

template<typename T, size_t N>
void write(std::ostream& out, const std::array<T, N>& array);

template<typename T>
void write(std::ostream& out, const std::vector<T>& vector);

template<typename T, size_t N>
void write(std::ostream& out, const std::array<T, N>& array) {
	out << "[";
	for(size_t i = 0; i < N; ++i) {
		if(i > 0) {
			out << ", ";
		}
		vnx::type<T>().write(out, array[i]);
	}
	out << "]";
}

template<typename T>
void write(std::ostream& out, const std::vector<T>& vector) {
	write_list(out, vector.begin(), vector.end());
}

template<typename K, typename V>
void write(std::ostream& out, const std::pair<K, V>& value) {
	out << "[";
	vnx::type<K>().write(out, value.first);
	out << ", ";
	vnx::type<V>().write(out, value.second);
	out << "]";
}

template<typename K, typename V>
void write(std::ostream& out, const std::map<K, V>& map) {
	write_list(out, map.begin(), map.end());
}

template<class Iter>
void write_list(std::ostream& out, Iter first, Iter last) {
	out << "[";
	for(Iter it = first; it != last; ++it) {
		if(it != first) {
			out << ", ";
		}
		vnx::type<typename Iter::value_type>().write(out, *it);
	}
	out << "]";
}

template<typename T>
void write(std::ostream& out, std::shared_ptr<T> value) {
	if(value) {
		value->write(out);
	} else {
		out << "{}";
	}
}

template<typename T>
void write(std::ostream& out, const T* data, const size_t size) {
	out << "[";
	for(size_t i = 0; i < size; ++i) {
		if(i > 0) {
			out << ", ";
		}
		out << data[i];
	}
	out << "]";
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
		write(out, data, total_size);
	} else {
		out << "{\"size\": ";
		write(out, size);
		out << ", \"data\": ";
		write(out, data, total_size);
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

template<typename T>
std::string to_string(const T& value) {
	std::ostringstream stream;
	vnx::type<T>().write(stream, value);
	return stream.str();
}

inline std::string to_string(const char* value) {
	return to_string(std::string(value));
}

template<typename T>
const TypeCode* write_type_code(TypeOutput& out) {
	auto iter = out.type_map.find(T::VNX_CODE_HASH);
	if(iter != out.type_map.end()) {
		return iter->second;
	}
	const TypeCode* type_code = vnx::get_type_code(T::VNX_CODE_HASH);
	if(type_code) {
		out.write_type_code(type_code);
	}
	return type_code;
}

template<typename T>
void write_class_header(TypeOutput& out) {
	char* const buf = out.write(10);
	write_value(buf, uint16_t(CODE_TYPE));
	write_value(buf + 2, uint64_t(T::VNX_CODE_HASH));
}

void write_class_header(TypeOutput& out, const TypeCode* type_code);

void write_to_file(const std::string& file_name, const Value& value);

void write_to_file(const std::string& file_name, std::shared_ptr<const Value> value);


} // vnx

#endif /* INCLUDE_VNX_OUTPUT_H_ */

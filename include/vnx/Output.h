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

#include <cstdio>
#include <sstream>


namespace vnx {

inline void write_value(void* buf, const bool_t& value) {
	*((uint8_t*)buf) = value;
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

template<bool, size_t N>
inline void write_value(char* buf, const std::array<bool, N>& array) {
	for(size_t i = 0; i < N; ++i) {
		write_value(buf + i, array[i]);
	}
}

inline void write(TypeOutput& out, const bool_t& value, const TypeCode* type_code = 0, const uint16_t* code = 0) {
	*((uint8_t*)out.write(sizeof(uint8_t))) = value;
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

void write_dynamic(TypeOutput& out, const bool_t& value);
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

void write_padding(TypeOutput& out, uint32_t size);

void write_byte_code(TypeOutput& out, const uint16_t* code, uint16_t code_size);

void write(TypeOutput& out, const std::string& string, const TypeCode* type_code, const uint16_t* code);

void write_dynamic(TypeOutput& out, const std::string& string);

template<typename T>
void write(TypeOutput& out, const std::shared_ptr<T>& value, const TypeCode* type_code = 0, const uint16_t* code = 0);

template<typename T>
void write(std::ostream& out, const std::shared_ptr<T>& value);

template<typename T, size_t N>
void write(TypeOutput& out, const std::array<T, N>& array, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void write(TypeOutput& out, const std::vector<T>& vector, const TypeCode* type_code, const uint16_t* code);

template<typename K, typename V>
void write(TypeOutput& out, const std::map<K, V>& map, const TypeCode* type_code, const uint16_t* code);

template<typename T, size_t N>
void write(TypeOutput& out, const std::array<T, N>& array, const TypeCode* type_code, const uint16_t* code) {
	for(size_t i = 0; i < N; ++i) {
		vnx::type<T>().write(out, array[i], type_code, code);
	}
}

template<typename T, size_t N>
void write_dynamic(TypeOutput& out, const std::array<T, N>& array) {
	if(N > VNX_MAX_STATIC_SIZE) {
		throw std::invalid_argument("write_dynamic(std::array<T, N>): N > VNX_MAX_STATIC_SIZE");
	}
	const uint16_t value_code = vnx::get_value_code<T>();
	if(value_code == CODE_NULL) {
		throw std::invalid_argument("write_dynamic(std::array<T, N>): unsupported typename T");
	}
	char* buf = out.write(8);
	write_value(buf, (uint16_t)3);
	write_value(buf + 2, (uint16_t)CODE_ARRAY);
	write_value(buf + 4, (uint16_t)N);
	write_value(buf + 6, (uint16_t)value_code);
	out.write(array.data(), N * sizeof(T));
}

template<typename T>
void write(TypeOutput& out, const std::vector<T>& vector, const TypeCode* type_code, const uint16_t* code) {
	if(vector.size() > VNX_MAX_SIZE) {
		throw std::invalid_argument("write(std::vector<T>): size > VNX_MAX_SIZE");
	}
	write(out, (uint32_t)vector.size());
	const size_t value_size = code ? get_value_size(code[1]) : 0;
	if(sizeof(T) == value_size) {
		out.write(vector.data(), vector.size() * value_size);
	} else {
		const uint16_t* value_code = code + 1;
		for(const T& elem : vector) {
			vnx::type<T>().write(out, elem, type_code, value_code);
		}
	}
}

template<typename T>
void write_dynamic(TypeOutput& out, const std::vector<T>& vector) {
	if(vector.size() > VNX_MAX_SIZE) {
		throw std::invalid_argument("write_dynamic(std::vector<T>): size > VNX_MAX_SIZE");
	}
	const uint16_t value_code = vnx::get_value_code<T>();
	if(value_code == CODE_NULL) {
		throw std::invalid_argument("write_dynamic(std::vector<T>): unsupported typename T");
	}
	char* buf = out.write(10);
	write_value(buf, (uint16_t)2);
	write_value(buf + 2, (uint16_t)CODE_LIST);
	write_value(buf + 4, (uint16_t)value_code);
	write_value(buf + 6, (uint32_t)vector.size());
	out.write(vector.data(), vector.size() * sizeof(T));
}

template<typename T>
void write_dynamic(TypeOutput& out, const T* data, const size_t size) {
	if(size > VNX_MAX_SIZE) {
		throw std::invalid_argument("write_dynamic(T*): size > VNX_MAX_SIZE");
	}
	const uint16_t value_code = vnx::get_value_code<T>();
	if(value_code == CODE_NULL) {
		throw std::invalid_argument("write_dynamic(T*): unsupported typename T");
	}
	char* buf = out.write(10);
	write_value(buf, (uint16_t)2);
	write_value(buf + 2, (uint16_t)CODE_LIST);
	write_value(buf + 4, (uint16_t)value_code);
	write_value(buf + 6, (uint32_t)size);
	out.write(data, size * sizeof(T));
}

template<typename K, typename V>
void write(TypeOutput& out, const std::map<K, V>& map, const TypeCode* type_code, const uint16_t* code) {
	if(map.size() > VNX_MAX_SIZE) {
		throw std::invalid_argument("write(std::map<K, V>): size > VNX_MAX_SIZE");
	}
	write(out, (uint32_t)map.size());
	const uint16_t* key_code = code + 2;
	const uint16_t* value_code = code + (code ? code[1] : 0);
	for(const std::pair<K, V>& elem : map) {
		vnx::type<K>().write(out, elem.first, type_code, key_code);
		vnx::type<V>().write(out, elem.second, type_code, value_code);
	}
}

void write(TypeOutput& out, const Value& value);

void write(TypeOutput& out, const Value* value);

template<typename T>
void write(TypeOutput& out, const std::shared_ptr<T>& value, const TypeCode* type_code, const uint16_t* code) {
	if(value) {
		value->write(out, 0, 0);
	} else {
		write(out, uint16_t(CODE_NULL));
	}
}

template<typename T>
void type<T>::write(TypeOutput& out, const T& value, const TypeCode* type_code, const uint16_t* code) {
	vnx::write(out, value, type_code, code);
}


inline void write(std::ostream& out, const uint8_t& value) { out << size_t(value); }
inline void write(std::ostream& out, const uint16_t& value) { out << value; }
inline void write(std::ostream& out, const uint32_t& value) { out << value; }
inline void write(std::ostream& out, const uint64_t& value) { out << value; }
inline void write(std::ostream& out, const int8_t& value) { out << ssize_t(value); }
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
void write(std::ostream& out, const std::shared_ptr<T>& value);

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
void write(std::ostream& out, const std::shared_ptr<T>& value) {
	if(value) {
		value->write(out);
	} else {
		out << "{}";
	}
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
	write_value(buf, uint16_t(CODE_CLASS));
	write_value(buf + 2, T::VNX_CODE_HASH);
}

void write_class_header(TypeOutput& out, const TypeCode* type_code);

template<typename T>
void write_to_file(const std::string& file_name, const T& value) {
	::FILE* file = ::fopen(file_name.c_str(), "wb");
	if(!file) {
		throw std::runtime_error("fopen('" + file_name + "') failed!");
	}
	FileOutputStream stream(file);
	TypeOutput out(&stream);
	vnx::write(out, value);
	out.flush();
	::fclose(file);
}

template<typename T>
void write_to_file(const std::string& file_name, std::shared_ptr<const T> value) {
	if(value) {
		write_to_file(file_name, *value);
	}
}


} // vnx

#endif /* INCLUDE_VNX_OUTPUT_H_ */

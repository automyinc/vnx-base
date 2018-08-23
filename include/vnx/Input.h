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

void skip(TypeInput& in);

void skip(TypeInput& in, const TypeCode* type_code, const uint16_t* code);

uint16_t read_byte_code(TypeInput& in, uint16_t* code);

inline void read(TypeInput& in, bool& value) { value = *((uint8_t*)in.read(sizeof(uint8_t))); }
inline void read(TypeInput& in, uint8_t& value) { value = *((uint8_t*)in.read(sizeof(uint8_t))); }
inline void read(TypeInput& in, uint16_t& value) { value = *((uint16_t*)in.read(sizeof(uint16_t))); }
inline void read(TypeInput& in, uint32_t& value) { value = *((uint32_t*)in.read(sizeof(uint32_t))); }
inline void read(TypeInput& in, uint64_t& value) { value = *((uint64_t*)in.read(sizeof(uint64_t))); }
inline void read(TypeInput& in, int8_t& value) { value = *((int8_t*)in.read(sizeof(int8_t))); }
inline void read(TypeInput& in, int16_t& value) { value = *((int16_t*)in.read(sizeof(int16_t))); }
inline void read(TypeInput& in, int32_t& value) { value = *((int32_t*)in.read(sizeof(int32_t))); }
inline void read(TypeInput& in, int64_t& value) { value = *((int64_t*)in.read(sizeof(int64_t))); }
inline void read(TypeInput& in, float32_t& value) { value = *((float32_t*)in.read(sizeof(float32_t))); }
inline void read(TypeInput& in, float64_t& value) { value = *((float64_t*)in.read(sizeof(float64_t))); }
inline void read(TypeInput& in, Hash64& value) { value = Hash64(*((uint64_t*)in.read(sizeof(uint64_t)))); }

inline void read_value(const void* buf, bool& value) { value = *((uint8_t*)buf); }
inline void read_value(const void* buf, uint8_t& value) { value = *((uint8_t*)buf); }
inline void read_value(const void* buf, uint16_t& value) { value = *((uint16_t*)buf); }
inline void read_value(const void* buf, uint32_t& value) { value = *((uint32_t*)buf); }
inline void read_value(const void* buf, uint64_t& value) { value = *((uint64_t*)buf); }
inline void read_value(const void* buf, int8_t& value) { value = *((int8_t*)buf); }
inline void read_value(const void* buf, int16_t& value) { value = *((int16_t*)buf); }
inline void read_value(const void* buf, int32_t& value) { value = *((int32_t*)buf); }
inline void read_value(const void* buf, int64_t& value) { value = *((int64_t*)buf); }
inline void read_value(const void* buf, float32_t& value) { value = *((float32_t*)buf); }
inline void read_value(const void* buf, float64_t& value) { value = *((float64_t*)buf); }
inline void read_value(const void* buf, Hash64& value) { value = Hash64(*((uint64_t*)buf)); }

template<typename T>
inline void read_value(const void* buf, T& value, const uint16_t* code) {
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
		default: value = T();
	}
}

template<typename T, size_t N>
inline void read_value(const char* buf, std::array<T, N>& array, const uint16_t* code) {
	if(!code || code[0] != CODE_ARRAY) {
		array = {};
		return;
	}
	const size_t size = code[1] <= N ? code[1] : N;
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

template<typename T>
inline void read_value(TypeInput& in, T& value, const TypeCode* type_code, const uint16_t* code) {
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
		case CODE_DYNAMIC: read_dynamic_value(in, value); return;
		default:
			value = T();
			skip(in, type_code, code);
	}
}

template<typename T>
void read_dynamic_value(TypeInput& in, T& value) {
	uint16_t code[VNX_MAX_BYTE_CODE_SIZE];
	read_byte_code(in, code);
	read_value(in, value, 0, code);
}

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

void read(TypeInput& in, std::string& string, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void read(TypeInput& in, std::shared_ptr<T>& value, const TypeCode* type_code, const uint16_t* code);

template<typename T, size_t N>
void read(TypeInput& in, std::array<T, N>& array, const TypeCode* type_code, const uint16_t* code);

template<typename T>
void read(TypeInput& in, std::vector<T>& vector, const TypeCode* type_code, const uint16_t* code);

template<typename K, typename V>
void read(TypeInput& in, std::map<K, V>& map, const TypeCode* type_code, const uint16_t* code);

template<typename T, size_t N>
void read(TypeInput& in, std::array<T, N>& array, const TypeCode* type_code, const uint16_t* code) {
	if(!code || code[0] != CODE_ARRAY) {
		array = {};
		skip(in, type_code, code);
		return;
	}
	const size_t size = code[1];
	const uint16_t* value_code = code + 2;
	const size_t value_size = get_value_size(value_code[0]);
	if(get_value_code<T>() == value_code[0] && sizeof(T) == value_size && size <= N) {
		in.read((char*)array.data(), size * sizeof(T));
	} else {
		for(size_t i = 0; i < size; ++i) {
			if(i < N) {
				vnx::type<T>().read(in, array[i], type_code, value_code);
			} else {
				skip(in, type_code, value_code);
			}
		}
	}
	for(size_t i = size; i < N; ++i) {
		array[i] = T();
	}
}

template<typename T>
void read(TypeInput& in, std::vector<T>& vector, const TypeCode* type_code, const uint16_t* code) {
	if(!code || code[0] != CODE_LIST) {
		vector.clear();
		skip(in, type_code, code);
		return;
	}
	uint32_t size;
	read(in, size);
	vector.resize(size);
	const uint16_t* value_code = code + 1;
	const size_t value_size = get_value_size(value_code[0]);
	if(get_value_code<T>() == value_code[0] && sizeof(T) == value_size) {
		in.read((char*)vector.data(), size * sizeof(T));
	} else {
		for(uint32_t i = 0; i < size; ++i) {
			vnx::type<T>().read(in, vector[i], type_code, value_code);
		}
	}
}

template<typename K, typename V>
void read(TypeInput& in, std::map<K, V>& map, const TypeCode* type_code, const uint16_t* code) {
	map.clear();
	if(!code || code[0] != CODE_MAP) {
		skip(in, type_code, code);
		return;
	}
	uint32_t size;
	read(in, size);
	const uint16_t* key_code = code + 2;
	const uint16_t* value_code = code + code[1];
	for(size_t i = 0; i < size; ++i) {
		K key;
		vnx::type<K>().read(in, key, type_code, key_code);
		V& value = map[key];
		vnx::type<V>().read(in, value, type_code, value_code);
	}
}

template<typename K, typename V>
void read(TypeInput& in, std::pair<K, V>& value, const TypeCode* type_code, const uint16_t* code) {
	if(!code || code[0] != CODE_TUPLE || code[1] != 2) {
		value = std::pair<K, V>();
		skip(in, type_code, code);
		return;
	}
	vnx::type<K>().read(in, value.first, type_code, code + code[2]);
	vnx::type<V>().read(in, value.second, type_code, code + code[3]);
}

template<typename T, size_t N>
void read_matrix(TypeInput& in, T* data, const std::array<size_t, N>& size, const uint16_t* code) {
	size_t total_size = 1;
	for(size_t i = 0; i < N; ++i) {
		total_size *= size[i];
	}
	if(code && code[0] == CODE_MATRIX && code[1] == N) {
		bool is_same = true;
		for(size_t i = 0; i < N; ++i) {
			is_same = is_same && code[2 + i] == size[i];
		}
		if(is_same) {
			const uint16_t* value_code = code + 2 + N;
			const size_t value_size = get_value_size(value_code[0]);
			if(value_size) {
				if(get_value_code<T>() == value_code[0] && sizeof(T) == value_size) {
					in.read((char*)data, total_size * sizeof(T));
				} else {
					const char* buf = in.read(total_size * value_size);
					for(size_t i = 0; i < total_size; ++i) {
						read_value(buf + i * value_size, data[i], value_code);
					}
				}
				return;
			} else {
				for(size_t i = 0; i < total_size; ++i) {
					vnx::type<T>().read(in, data[i], 0, value_code);
				}
				return;
			}
		}
	}
	for(size_t i = 0; i < total_size; ++i) {
		data[i] = T();
	}
	skip(in, 0, code);
}

template<size_t N>
void read_image_size(TypeInput& in, std::array<size_t, N>& size, const uint16_t* code) {
	if(code && code[0] == CODE_IMAGE && code[1] == N) {
		const char* buf = in.read(4 * N);
		for(size_t i = 0; i < N; ++i) {
			uint32_t size_ = 0;
			read_value(buf + 4 * i, size_);
			size[i] = size_;
		}
	} else {
		for(size_t i = 0; i < N; ++i) {
			size[i] = 0;
		}
	}
}

template<typename T, size_t N>
void read_image_data(TypeInput& in, T* data, const std::array<size_t, N>& size, const uint16_t* code) {
	if(code && code[0] == CODE_IMAGE && code[1] == N && data) {
		size_t total_size = 1;
		for(size_t i = 0; i < N; ++i) {
			total_size *= size[i];
		}
		const uint16_t* value_code = code + 2;
		const size_t value_size = get_value_size(value_code[0]);
		if(get_value_code<T>() == value_code[0] && sizeof(T) == value_size) {
			in.read((char*)data, total_size * sizeof(T));
		} else {
			for(size_t i = 0; i < total_size; ++i) {
				vnx::type<T>().read(in, data[i], 0, value_code);
			}
		}
	} else {
		skip(in, 0, code);
	}
}

std::shared_ptr<Value> read(TypeInput& in);

template<typename T>
void read(TypeInput& in, T& value) {
	std::shared_ptr<T> tmp = std::dynamic_pointer_cast<T>(read(in));
	if(tmp) {
		value = *tmp;
	} else {
		value = T();
	}
}

template<typename T>
void read(TypeInput& in, T& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] != CODE_ANY) {
		skip(in, type_code, code);
		value = T();
	} else {
		read(in, value);
	}
}

template<typename T>
void read(TypeInput& in, std::shared_ptr<T>& value) {
	value = std::dynamic_pointer_cast<T>(read(in));
}

template<typename T>
void read(TypeInput& in, std::shared_ptr<T>& value, const TypeCode* type_code, const uint16_t* code) {
	if(code && code[0] != CODE_ANY) {
		skip(in, type_code, code);
		value = 0;
	} else {
		read(in, value);
	}
}

template<typename T>
void type<T>::read(TypeInput& in, T& value, const TypeCode* type_code, const uint16_t* code) {
	vnx::read(in, value, type_code, code);
}

template<typename T>
void read_dynamic(TypeInput& in, T& value) {
	uint16_t code[VNX_MAX_BYTE_CODE_SIZE];
	read_byte_code(in, code);
	switch(code[0]) {
		case CODE_ANY:
			read(in, value);
			break;
		case CODE_DYNAMIC:
			read_dynamic(in, value);
			break;
		default:
			vnx::type<T>().read(in, value, 0, code);
	}
}

template<typename T>
void read_dynamic_list_size(TypeInput& in, uint16_t* code_, size_t& size_) {
	read_byte_code(in, code_);
	if(code_[0] == CODE_LIST) {
		uint32_t size;
		read(in, size);
		size_ = size;
	} else {
		size_ = 0;
	}
}

template<typename T>
void read_dynamic_list_data(TypeInput& in, T* data_, const uint16_t* code_, const size_t& size_) {
	if(code_[0] == CODE_LIST && data_) {
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

void from_string(const std::string& str, std::map<std::string, std::string>& value);

template<typename T>
void from_string(const std::string& str, std::shared_ptr<const T>& value);

bool read_value(std::istream& in, std::string& out, bool want_string = false, char stop_char = 0);

bool read_object(std::istream& in, std::map<std::string, std::string>& object);

inline void read(std::istream& in, bool& value) { int tmp; in >> tmp; value = tmp; }
inline void read(std::istream& in, uint8_t& value) { int tmp; in >> tmp; value = tmp; }
inline void read(std::istream& in, uint16_t& value) { in >> value; }
inline void read(std::istream& in, uint32_t& value) { in >> value; }
inline void read(std::istream& in, uint64_t& value) { in >> value; }
inline void read(std::istream& in, int8_t& value) { int tmp; in >> tmp; value = tmp; }
inline void read(std::istream& in, int16_t& value) { in >> value; }
inline void read(std::istream& in, int32_t& value) { in >> value; }
inline void read(std::istream& in, int64_t& value) { in >> value; }
inline void read(std::istream& in, float32_t& value) { in >> value; }
inline void read(std::istream& in, float64_t& value) { in >> value; }

void read(std::istream& in, std::string& value);

std::shared_ptr<Variant> read(std::istream& in);

template<typename T, size_t N>
void read(std::istream& in, std::array<T, N>& array) {
	int stack = 0;
	int k = 0;
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
	for(int i = k; i < N; ++i) {
		array[i] = T();
	}
}

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
			from_string(str, object);
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

template<typename T>
void from_string(const std::string& str, T& value) {
	std::istringstream stream;
	stream.str(str);
	vnx::type<T>().read(stream, value);
}

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

void read_type_code(TypeInput& in);

std::shared_ptr<Value> read_from_file(const std::string& file_name);

template<typename T>
std::shared_ptr<T> read_from_file(const std::string& file_name) {
	return std::dynamic_pointer_cast<T>(read_from_file(file_name));
}

std::string to_string(TypeInput& in);

std::string to_string(TypeInput& in, const TypeCode* type_code, const uint16_t* code);


} // vnx

#endif /* INCLUDE_VNX_INPUT_H_ */

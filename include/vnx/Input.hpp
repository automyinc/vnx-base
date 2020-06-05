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

#ifndef INCLUDE_VNX_INPUT_HPP_
#define INCLUDE_VNX_INPUT_HPP_

#include <vnx/Input.h>
#include <vnx/Object.h>
#include <vnx/Variant.h>


namespace vnx {

/** \brief Reads a Value from the input stream.
 *
 * Same as read(TypeInput& in) but not at top level, ie. this function expects a code.
 * In case of incompatible data a nullptr will be returned.
 * Compatible with CODE_ANY, CODE_DYNAMIC and CODE_OBJECT.
 */
template<typename T>
void read(TypeInput& in, std::shared_ptr<T>& value, const TypeCode* type_code, const uint16_t* code) {
	if(!code) {
		throw std::logic_error("!code");
	}
	switch(code[0]) {
		case CODE_ANY:
		case CODE_ALT_ANY:
			value = std::dynamic_pointer_cast<T>(read(in));
			break;
		case CODE_DYNAMIC:
		case CODE_ALT_DYNAMIC:
			read_dynamic(in, value);
			break;
		case CODE_OBJECT:
		case CODE_ALT_OBJECT: {
			Object tmp;
			read(in, tmp, type_code, code);
			value = std::dynamic_pointer_cast<T>(tmp.to_value());
			break;
		}
		default:
			value = 0;
			skip(in, type_code, code);
	}
}

template<typename T>
void from_string(const std::string& str, T& value);

template<typename T>
void from_string(const std::string& str, std::shared_ptr<T>& value);

template<typename T>
void from_string(const std::string& str, std::shared_ptr<const T>& value);

/** \brief Reads a static array from the JSON stream
 *
 * Example: [1, 2, 3] \n
 * If the input array is smaller than \p array the left-over elements are default initialized.
 */
template<typename T, size_t N>
void read(std::istream& in, std::array<T, N>& array) {
	std::vector<std::string> tmp;
	read_array(in, tmp);
	for(size_t i = 0; i < N; ++i) {
		T next = T();
		if(i < tmp.size()) {
			from_string(tmp[i], next);
		}
		array[i] = std::move(next);
	}
}

/** \brief Reads a dynamic array from the JSON stream
 *
 * Example: [1, 2, 3]
 */
template<typename T>
void read(std::istream& in, std::vector<T>& vector) {
	vector.clear();
	std::vector<std::string> tmp;
	read_array(in, tmp);
	for(const auto& value : tmp) {
		T next = T();
		from_string(value, next);
		vector.emplace_back(std::move(next));
	}
}

/** \brief Reads a pair from the JSON stream
 *
 * Example: ["key", "value"]
 */
template<typename K, typename V>
void read(std::istream& in, std::pair<K, V>& pair) {
	std::vector<std::string> tmp;
	read_array(in, tmp);
	if(tmp.size() == 2) {
		from_string(tmp[0], pair.first);
		from_string(tmp[1], pair.second);
	} else {
		pair = std::pair<K, V>();
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
	const Variant tmp = read(in);
	if(tmp.is_list()) {
		const auto list = tmp.to<std::vector<std::vector<Variant>>>();
		for(const auto& entry : list) {
			if(entry.size() == 2) {
				entry[1].to(map[entry[0].to<K>()]);
			}
		}
	} else if(tmp.is_object()) {
		const auto object = tmp.to_object();
		for(const auto& entry : object.field) {
			K key = K();
			from_string(entry.first, key);
			entry.second.to(map[key]);
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
	bool is_valid = false;
	std::vector<T> values;
	const Variant tmp = read(in);
	if(tmp.is_list()) {
		is_valid = true;
		tmp.to(values);
	} else if(tmp.is_object()) {
		const auto object = tmp.to_object();
		for(const auto& entry : object.field) {
			if(entry.first == "size") {
				const auto size_ = entry.second.to<std::vector<int>>();
				if(size_.size() == N) {
					is_valid = true;
					for(size_t i = 0; i < N; ++i) {
						if(size_[i] != int(size[i])) {
							is_valid = false;
							break;
						}
					}
				}
			} else if(entry.first == "data") {
				entry.second.to(values);
			}
		}
	}
	is_valid = is_valid && (values.size() == total_size);
	for(size_t i = 0; i < total_size; ++i) {
		if(is_valid && i < values.size()) {
			data[i] = values[i];
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
/// If \p value is NULL will attempt to read polymorphic type via "__type" field.
template<typename T>
void from_string(const std::string& str, std::shared_ptr<T>& value) {
	if(!value) {
		Object tmp;
		vnx::from_string(str, tmp);
		const auto* type_code = vnx::get_type_code(tmp["__type"].to_string_value());
		if(type_code) {
			value = std::dynamic_pointer_cast<T>(type_code->create_value());
		}
		if(!value) {
			value = T::create();
		}
		value->from_object(tmp);
	} else {
		from_string(str, *value);
	}
}

/// Reads a Value of type T from the JSON stream
template<typename T>
void from_string(const std::string& str, std::shared_ptr<const T>& value) {
	std::shared_ptr<T> tmp;
	from_string(str, tmp);
	value = tmp;
}


} // vnx

#endif /* INCLUDE_VNX_INPUT_HPP_ */

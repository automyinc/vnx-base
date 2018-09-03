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

#ifndef INCLUDE_VNX_TYPE_H_
#define INCLUDE_VNX_TYPE_H_

#include <stdint.h>

#include <string>
#include <vector>
#include <list>
#include <array>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <functional>
#include <stdexcept>
#include <memory>

#include <vnx/Hash64.h>
#include <vnx/Util.h>


/**
 * The maximum size of dynamic containers (ie. vector, map)
 */
#define VNX_MAX_SIZE 0xFFFFFFFF

/**
 * The maximum size of static containers (ie. array)
 */
#define VNX_MAX_STATIC_SIZE 0xFFFF

/**
 * The maximum size of dynamic code.
 * Absolute maximum is 255 to detect different byte order.
 */
#define VNX_MAX_BYTE_CODE_SIZE 32

/**
 * The buffer size for InputBuffer and OutputBuffer.
 * This is also the maximum combined size of all primitive fields in a struct or class.
 */
#define VNX_BUFFER_SIZE 16384


/// VNX Framework namespace
namespace vnx {

typedef bool bool_t;
typedef float float32_t;
typedef double float64_t;

class Visitor;
class Value;
class Variant;
class Topic;
class TypeCode;
class TypeInput;
class TypeOutput;

const TypeCode* register_type_code(std::shared_ptr<TypeCode> type_code);

const TypeCode* register_type_code(Hash64 hash, std::shared_ptr<TypeCode> type_code);

const TypeCode* get_type_code(Hash64 hash);

std::vector<const TypeCode*> get_all_type_codes();

const uint16_t* validate_code(const uint16_t* code, const TypeCode* type_code = 0, size_t size = size_t(-1), size_t pos = 0);

/** \brief Codes used by the VNX serialization type system.
 * 
 * Codes are limited to 8-bit but are serialized as 16-bit values to detect a different byte order.
 * Alternate (ALT_) codes are from machines with different byte order.
 */
enum {
	CODE_NULL = 0,				/// used for nullptr
	
	CODE_UINT8 = 1,				/// 8-bit unsigned integer
	CODE_UINT16 = 2,			/// 16-bit unsigned integer
	CODE_UINT32 = 3,			/// 32-bit unsigned integer
	CODE_UINT64 = 4,			/// 64-bit unsigned integer
	
	CODE_INT8 = 5,				/// 8-bit signed integer
	CODE_INT16 = 6,				/// 16-bit signed integer
	CODE_INT32 = 7,				/// 32-bit signed integer
	CODE_INT64 = 8,				/// 64-bit signed integer
	
	CODE_FLOAT = 9,				/// 32-bit IEEE floating point
	CODE_DOUBLE = 10,			/// 64-bit IEEE floating point
	
	CODE_ARRAY = 11,			/// static array (std::array), code = {11, <size>, <type code>}
	CODE_LIST = 12,				/// dynamic list (std::list or std::vector), code = {12, <type code>}, header = {UINT32 <size>}
	CODE_MAP = 13,				/// dynamic map (std::map), code = {13, <code offset for value type starting at 13>, <key type code>, <value type code>}, header = {UINT32 <size>}
	
	CODE_TYPE_CODE = 14,		/// code for a vnx::TypeCode
	CODE_TYPE = 15,				/// code for a type to follow, header = {15, UINT64 <code hash>}
	CODE_ANY = 16,				/// code for anything (currently only CODE_TYPE_CODE, CODE_TYPE, CODE_OBJECT, CODE_ANY or CODE_PADDING allowed) 
	CODE_DYNAMIC = 17,			/// code for dynamic code (ie. the actual code is in the data), header = {UINT16 <code size>}
	CODE_PADDING = 18,			/// code for zero padding (used by RecordWriter for example), header = {18, UINT32 <padding size>}
	CODE_STRUCT = 19,			/// code for nested struct, code = {19, <depends index>}
	
	CODE_MATRIX = 21,			/// static ND array, code = {21, <number of dimensions>, <size of dim 0>, <size of dim 1>, ..., <type code>}
	CODE_IMAGE = 22,			/// dynamic ND array, code = {22, <number of dimensions>, <type code>}, header = {UINT32 <size of dim 0>, UINT32 <size of dim 1>, ...}
	CODE_TUPLE = 23,			/// array of different types, code = {23, <size>, <type code offset 0>, ..., <type code>, ...}
	CODE_OBJECT = 24,			/// same as CODE_MAP with {MAP, 4, LIST, INT8, DYNAMIC} but intended to be a dynamically defined type instead of a map
	
	CODE_MAGIC = 0x3713,		/// magic number for VNX to detect binary files containing serialized data
	CODE_NONE = 0xFFFF,			/// used to detect binary file vs. text file, irrespective of byte order
	
	CODE_ALT_UINT8 = 0x100,
	CODE_ALT_UINT16 = 0x200,
	CODE_ALT_UINT32 = 0x300,
	CODE_ALT_UINT64 = 0x400,
	
	CODE_ALT_INT8 = 0x500,
	CODE_ALT_INT16 = 0x600,
	CODE_ALT_INT32 = 0x700,
	CODE_ALT_INT64 = 0x800,
	
	CODE_ALT_FLOAT = 0x900,
	CODE_ALT_DOUBLE = 0xA00,
	
	CODE_ALT_ARRAY = 0xB00,
	CODE_ALT_LIST = 0xC00,
	CODE_ALT_MAP = 0xD00,
	
	CODE_ALT_TYPE_CODE = 0xE00,
	CODE_ALT_TYPE = 0xF00,
	CODE_ALT_ANY = 0x1000,
	CODE_ALT_DYNAMIC = 0x1100,
	CODE_ALT_PADDING = 0x1200,
	CODE_ALT_STRUCT = 0x1300,
	
	CODE_ALT_MATRIX = 0x1500,
	CODE_ALT_IMAGE = 0x1600,
	CODE_ALT_TUPLE = 0x1700,
	CODE_ALT_OBJECT = 0x1800,
	
	CODE_ALT_MAGIC = 0x1337,
	
};

template<typename T>
uint16_t get_value_code() {
	return CODE_NONE;
}

template<> inline uint16_t get_value_code<bool>() { return sizeof(bool) == 1 ? CODE_UINT8 : CODE_NULL; }
template<> inline uint16_t get_value_code<uint8_t>() { return CODE_UINT8; }
template<> inline uint16_t get_value_code<uint16_t>() { return CODE_UINT16; }
template<> inline uint16_t get_value_code<uint32_t>() { return CODE_UINT32; }
template<> inline uint16_t get_value_code<uint64_t>() { return CODE_UINT64; }
template<> inline uint16_t get_value_code<char>() { return CODE_INT8; }
template<> inline uint16_t get_value_code<int8_t>() { return CODE_INT8; }
template<> inline uint16_t get_value_code<int16_t>() { return CODE_INT16; }
template<> inline uint16_t get_value_code<int32_t>() { return CODE_INT32; }
template<> inline uint16_t get_value_code<int64_t>() { return CODE_INT64; }
template<> inline uint16_t get_value_code<float32_t>() { return CODE_FLOAT; }
template<> inline uint16_t get_value_code<float64_t>() { return CODE_DOUBLE; }

inline size_t get_value_size(uint16_t code) {
	switch(code) {
		case CODE_UINT8: return 1;
		case CODE_UINT16: return 2;
		case CODE_UINT32: return 4;
		case CODE_UINT64: return 8;
		case CODE_INT8: return 1;
		case CODE_INT16: return 2;
		case CODE_INT32: return 4;
		case CODE_INT64: return 8;
		case CODE_FLOAT: return 4;
		case CODE_DOUBLE: return 8;
		case CODE_ALT_UINT8: return 1;
		case CODE_ALT_UINT16: return 2;
		case CODE_ALT_UINT32: return 4;
		case CODE_ALT_UINT64: return 8;
		case CODE_ALT_INT8: return 1;
		case CODE_ALT_INT16: return 2;
		case CODE_ALT_INT32: return 4;
		case CODE_ALT_INT64: return 8;
		case CODE_ALT_FLOAT: return 4;
		case CODE_ALT_DOUBLE: return 8;
		default: return 0;
	}
}

template<typename T>
bool is_equivalent(uint16_t code) {
	return get_value_code<T>() == code;
}

template<>
inline bool is_equivalent<uint8_t>(uint16_t code) {
	switch(code) {
		case CODE_UINT8:
		case CODE_INT8:
		case CODE_ALT_UINT8:
		case CODE_ALT_INT8:
			return true;
	}
	return false;
}

template<>
inline bool is_equivalent<uint16_t>(uint16_t code) {
	switch(code) {
		case CODE_UINT16:
		case CODE_INT16:
			return true;
	}
	return false;
}

template<>
inline bool is_equivalent<uint32_t>(uint16_t code) {
	switch(code) {
		case CODE_UINT32:
		case CODE_INT32:
			return true;
	}
	return false;
}

template<>
inline bool is_equivalent<uint64_t>(uint16_t code) {
	switch(code) {
		case CODE_UINT64:
		case CODE_INT64:
			return true;
	}
	return false;
}

template<>
inline bool is_equivalent<int8_t>(uint16_t code) {
	return is_equivalent<uint8_t>(code);
}

template<>
inline bool is_equivalent<int16_t>(uint16_t code) {
	return is_equivalent<uint16_t>(code);
}

template<>
inline bool is_equivalent<int32_t>(uint16_t code) {
	return is_equivalent<uint32_t>(code);
}

template<>
inline bool is_equivalent<int64_t>(uint16_t code) {
	return is_equivalent<uint64_t>(code);
}

inline void create_dynamic_code(std::vector<uint16_t>& code, const bool& value) { code.push_back(CODE_UINT8); }
inline void create_dynamic_code(std::vector<uint16_t>& code, const uint8_t& value) { code.push_back(CODE_UINT8); }
inline void create_dynamic_code(std::vector<uint16_t>& code, const uint16_t& value) { code.push_back(CODE_UINT16); }
inline void create_dynamic_code(std::vector<uint16_t>& code, const uint32_t& value) { code.push_back(CODE_UINT32); }
inline void create_dynamic_code(std::vector<uint16_t>& code, const uint64_t& value) { code.push_back(CODE_UINT64); }
inline void create_dynamic_code(std::vector<uint16_t>& code, const char& value) { code.push_back(CODE_INT8); }
inline void create_dynamic_code(std::vector<uint16_t>& code, const int8_t& value) { code.push_back(CODE_INT8); }
inline void create_dynamic_code(std::vector<uint16_t>& code, const int16_t& value) { code.push_back(CODE_INT16); }
inline void create_dynamic_code(std::vector<uint16_t>& code, const int32_t& value) { code.push_back(CODE_INT32); }
inline void create_dynamic_code(std::vector<uint16_t>& code, const int64_t& value) { code.push_back(CODE_INT64); }
inline void create_dynamic_code(std::vector<uint16_t>& code, const float32_t& value) { code.push_back(CODE_FLOAT); }
inline void create_dynamic_code(std::vector<uint16_t>& code, const float64_t& value) { code.push_back(CODE_DOUBLE); }

inline void create_dynamic_code(std::vector<uint16_t>& code, const std::string& value) {
	code.push_back(CODE_LIST);
	code.push_back(CODE_INT8);
}

template<typename T, size_t N>
void create_dynamic_code(std::vector<uint16_t>& code, const std::array<T, N>& value);

template<typename T>
void create_dynamic_code(std::vector<uint16_t>& code, const std::vector<T>& value);

template<typename T>
void create_dynamic_code(std::vector<uint16_t>& code, const std::list<T>& value);

template<typename T>
void create_dynamic_code(std::vector<uint16_t>& code, const std::set<T>& value);

template<typename T>
void create_dynamic_code(std::vector<uint16_t>& code, const std::unordered_set<T>& value);

template<typename K, typename V>
void create_dynamic_code(std::vector<uint16_t>& code, const std::map<K, V>& value);

template<typename K, typename V>
void create_dynamic_code(std::vector<uint16_t>& code, const std::unordered_map<K, V>& value);

template<typename K, typename V>
void create_dynamic_code(std::vector<uint16_t>& code, const std::pair<K, V>& value);

void create_dynamic_code(std::vector<uint16_t>& code, const Value& value);

void create_dynamic_code(std::vector<uint16_t>& code, std::shared_ptr<const Value> value);


class TypeField {
public:
	uint16_t version = 2;			/// type field version
	
	std::string name;				/// field name
	std::string value;				/// default value in JSON format
	std::vector<uint16_t> code;		/// field code
	bool is_extended = false;		/// extended means dynamic size
	
	/**
	 * The following fields are computed at runtime. They are not serialized.
	 */
	size_t index = 0;				/// field index in the original TypeCode::fields array
	size_t offset = 0;				/// byte offset in the original static data section
	size_t size = 0;				/// size in bytes
	
	int32_t native_index = -1;		/// field index in the native TypeCode::fields array
	
	void compile(const TypeCode* type_code);
	
};

class TypeCode {
public:
	TypeCode(bool is_native_ = false);
	
	uint16_t version = 2;	/// type code version
	
	Hash64 type_hash;		/// the identity of this type of _any_ version (ie. only depends on the full type name)
	Hash64 code_hash;		/// the identity of this type of a _specific_ version (changes when fields are added/removed or changed)
	
	std::vector<const TypeCode*> parents;		/// the inheritance line (used by instanceof())
	std::vector<const TypeCode*> depends;		/// the types which are used by this type's fields
	const vnx::TypeCode* return_type = 0;		/// in case of a method type this is the return type
	
	std::string name;							/// full unique name of the type (including the namespace)
	std::vector<TypeField> fields;
	std::vector<TypeField> static_fields;		/// ie. constants
	std::vector<const TypeCode*> methods;
	std::map<uint32_t, std::string> enum_map;			/// map from enum values to their names (only for enum types)
	std::map<std::string, std::string> alias_map;		/// map for field matching in case of changed field names
	
	bool is_enum = false;			/// if type is an enum
	bool is_class = false;			/// if type is a class (ie. inherits from Value)
	bool is_method = false;			/// if type is a method
	bool is_return = false;			/// if type is a method return type
	
	/**
	 * The following fields are computed at runtime. They are not serialized.
	 */
	bool is_native = false;
	size_t total_field_size = 0;
	std::vector<TypeField*> field_map;
	std::vector<TypeField*> ext_fields;
	std::map<std::string, uint32_t> inv_enum_map;
	
	std::function<std::shared_ptr<Value>(void)> create_value;		/// function that creates a new value of this type
	
	/**
	 * Must be called after de-serializing a TypeCode.
	 */
	void build();
	
	/**
	 * Returns true if this type is a sub-class (or direct match) of the given type.
	 */
	bool instanceof(Hash64 type_hash_) const;
	
private:
	void compile();
	
	void link();
	
	/**
	 * Will try to match this type to a native type.
	 * If successful we can deserialize this type into a native struct or class.
	 */
	void match(const TypeCode* native);
	
};

void read(TypeInput& in, TypeField& field, const TypeCode* type_code, const uint16_t* code);
void write(TypeOutput& out, const TypeField& field, const TypeCode* type_code, const uint16_t* code);

void read(TypeInput& in, TypeCode& type_code);
void write(TypeOutput& out, const TypeCode& type_code);


template<typename T>
struct type {
	void read(TypeInput& in, T& value, const TypeCode* type_code, const uint16_t* code);
	void write(TypeOutput& out, const T& value, const TypeCode* type_code, const uint16_t* code);
	void read(std::istream& in, T& value);
	void write(std::ostream& out, const T& value);
	void accept(Visitor& visitor, const T& value);
	void create_dynamic_code(std::vector<uint16_t>& code);
};

template<typename T>
void type<T>::create_dynamic_code(std::vector<uint16_t>& code) {
	vnx::create_dynamic_code(code, T());
}

template<typename T, size_t N>
void create_dynamic_code(std::vector<uint16_t>& code, const std::array<T, N>& value) {
	if(N > VNX_MAX_STATIC_SIZE) {
		throw std::invalid_argument("create_dynamic_code(std::array<T, N>): N > VNX_MAX_STATIC_SIZE");
	}
	code.push_back(CODE_ARRAY);
	code.push_back(N);
	vnx::type<T>().create_dynamic_code(code);
}

template<typename T>
void create_dynamic_code(std::vector<uint16_t>& code, const std::vector<T>& value) {
	code.push_back(CODE_LIST);
	vnx::type<T>().create_dynamic_code(code);
}

template<typename T>
void create_dynamic_code(std::vector<uint16_t>& code, const std::list<T>& value) {
	create_dynamic_code<T>(code, std::vector<T>());
}

template<typename T>
void create_dynamic_code(std::vector<uint16_t>& code, const std::set<T>& value) {
	create_dynamic_code<T>(code, std::vector<T>());
}

template<typename T>
void create_dynamic_code(std::vector<uint16_t>& code, const std::unordered_set<T>& value) {
	create_dynamic_code<T>(code, std::vector<T>());
}

template<typename K, typename V>
void create_dynamic_code(std::vector<uint16_t>& code, const std::map<K, V>& value) {
	const size_t begin = code.size();
	code.push_back(CODE_MAP);
	code.push_back(0);
	vnx::type<K>().create_dynamic_code(code);
	code[begin + 1] = uint16_t(code.size() - begin);
	vnx::type<V>().create_dynamic_code(code);
}

template<typename K, typename V>
void create_dynamic_code(std::vector<uint16_t>& code, const std::unordered_map<K, V>& value) {
	create_dynamic_code<K, V>(code, std::map<K, V>());
}

template<typename K, typename V>
void create_dynamic_code(std::vector<uint16_t>& code, const std::pair<K, V>& value) {
	const size_t begin = code.size();
	code.push_back(CODE_TUPLE);
	code.push_back(2);
	code.push_back(0);
	code.push_back(0);
	code[begin + 2] = uint16_t(code.size() - begin);
	vnx::type<K>().create_dynamic_code(code);
	code[begin + 3] = uint16_t(code.size() - begin);
	vnx::type<V>().create_dynamic_code(code);
}

inline void create_dynamic_code(std::vector<uint16_t>& code, const Value& value) {
	code.push_back(CODE_ANY);
}

inline void create_dynamic_code(std::vector<uint16_t>& code, std::shared_ptr<const Value> value) {
	code.push_back(CODE_ANY);
}


} // vnx

#endif /* INCLUDE_VNX_TYPE_H_ */

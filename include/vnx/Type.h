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
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <string>
#include <vector>
#include <list>
#include <array>
#include <map>
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <functional>
#include <stdexcept>
#include <memory>

#include <vnx/Hash64.h>
#include <vnx/Util.h>


/*
 * The maximum size of dynamic containers (ie. vector, map)
 */
#define VNX_MAX_SIZE 0xFFFFFFFF

/*
 * The maximum size of static containers (ie. array)
 */
#define VNX_MAX_STATIC_SIZE 0xFFFF

/*
 * The maximum size of dynamic code.
 */
#define VNX_MAX_BYTE_CODE_SIZE 32

/*
 * The buffer size for InputBuffer and OutputBuffer.
 * This is also the maximum combined size of all primitive fields in a struct or class.
 */
#define VNX_BUFFER_SIZE 16384

typedef bool bool_t;
typedef float float32_t;
typedef double float64_t;


namespace vnx {

class Visitor;
class Value;
class Topic;
class TypeCode;
class TypeInput;
class TypeOutput;

const TypeCode* register_type_code(std::shared_ptr<TypeCode> type_code);

const TypeCode* register_type_code(Hash64 hash, std::shared_ptr<TypeCode> type_code);

const TypeCode* get_type_code(Hash64 hash);

std::vector<const TypeCode*> get_all_type_codes();

enum {
	CODE_NULL = 0,
	
	CODE_UINT8 = 1,
	CODE_UINT16 = 2,
	CODE_UINT32 = 3,
	CODE_UINT64 = 4,
	
	CODE_INT8 = 5,
	CODE_INT16 = 6,
	CODE_INT32 = 7,
	CODE_INT64 = 8,
	
	CODE_FLOAT = 9,
	CODE_DOUBLE = 10,
	
	CODE_ARRAY = 11,			// static array (std::array)
	CODE_LIST = 12,				// dynamic list (std::list or std::vector)
	CODE_MAP = 13,				// dynamic map (std::map)
	
	CODE_TYPE_CODE = 14,		// code for a vnx::TypeCode
	CODE_CLASS = 15,			// code for a class (vnx::Value)
	CODE_ANY = 16,				// code for anything (currently only CODE_TYPE_CODE, CODE_CLASS or CODE_PADDING allowed) 
	CODE_DYNAMIC = 17,			// code for dynamic code (ie. the actual code is in the data)
	CODE_PADDING = 18,			// code for zero padding (used by RecordWriter for example)
};

template<typename T>
inline uint16_t get_value_code() {
	return CODE_NULL;
}

template<> inline uint16_t get_value_code<uint8_t>() { return CODE_UINT8; }
template<> inline uint16_t get_value_code<uint16_t>() { return CODE_UINT16; }
template<> inline uint16_t get_value_code<uint32_t>() { return CODE_UINT32; }
template<> inline uint16_t get_value_code<uint64_t>() { return CODE_UINT64; }
template<> inline uint16_t get_value_code<int8_t>() { return CODE_INT8; }
template<> inline uint16_t get_value_code<int16_t>() { return CODE_INT16; }
template<> inline uint16_t get_value_code<int32_t>() { return CODE_INT32; }
template<> inline uint16_t get_value_code<int64_t>() { return CODE_INT64; }
template<> inline uint16_t get_value_code<float32_t>() { return CODE_FLOAT; }
template<> inline uint16_t get_value_code<float64_t>() { return CODE_DOUBLE; }

inline int get_value_size(uint16_t code) {
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
	}
	return 0;
}


class TypeField {
public:
	bool is_extended = false;
	std::vector<uint16_t> code;
	std::string name;
	std::string value;
	
	uint32_t index = 0;
	uint32_t offset = 0;
	uint32_t size = 0;
	
	int32_t native_index = -1;
	
	void compile();
	
};


class TypeCode {
public:
	TypeCode(bool is_native_ = false);
	
	Hash64 type_hash;		// the identity of this type of _any_ version (ie. does not change ever)
	Hash64 code_hash;		// the identity of this type of a _specific_ version (changes when fields are added/removed or changed)
	
	std::vector<const TypeCode*> parents;		// the inheritance line (used by instanceof())
	std::vector<const TypeCode*> depends;		// the types which are used by this type's fields
	const vnx::TypeCode* return_type = 0;		// in case of a method type this is the return type
	
	std::string name;							// full unique name of the type (including the namespace)
	std::vector<TypeField> fields;
	std::vector<TypeField> static_fields;		// ie. constants
	std::vector<const TypeCode*> methods;
	std::map<uint32_t, std::string> enum_map;	// map from enum values to their names (only for enum types)
	
	/*
	 * The following fields are computed at runtime. They are not serialized.
	 */
	bool is_native = false;
	bool is_matched = false;
	uint32_t total_field_size = 0;
	std::vector<TypeField*> field_map;
	std::vector<TypeField*> ext_fields;
	std::map<std::string, uint32_t> inv_enum_map;
	
	/*
	 * The following field is only set for native types.
	 */
	std::function<std::shared_ptr<Value>(void)> create_value;		// function that creates a new value of this type
	
	/*
	 * Must be called after deserializing a TypeCode.
	 */
	void build();
	
	/*
	 * Returns true if this type is a sub-class (or direct match) of the given type.
	 */
	bool instanceof(Hash64 type_hash_) const;
	
private:
	void compile();
	
	void link();
	
	/*
	 * Will try to match this type to a native type.
	 * If successfull we can deserialize this type into a native struct or class.
	 */
	void match(const TypeCode* native);
	
};


void read(TypeInput& in, TypeField& field, const TypeCode* type_code, const uint16_t* code);
void write(TypeOutput& out, const TypeField& field, const TypeCode* type_code, const uint16_t* code);

void read(TypeInput& in, TypeCode& type_code);
void write(TypeOutput& out, const TypeCode& type_code);


} // vnx

#endif /* INCLUDE_VNX_TYPE_H_ */

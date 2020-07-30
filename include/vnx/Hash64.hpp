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

#ifndef INCLUDE_VNX_HASH64_HPP_
#define INCLUDE_VNX_HASH64_HPP_

#include <vnx/package.hxx>
#include <vnx/Hash64.h>
#include <vnx/Hash128.hpp>
#include <vnx/Util.h>
#include <vnx/Input.hpp>
#include <vnx/Output.hpp>
#include <vnx/Visitor.h>
#include <vnx/CRC64.h>


namespace vnx {

inline
Hash64::Hash64(const std::string& name) : value(hash64(name)) {}

inline
Hash64::Hash64(const Hash128& hash) : Hash64(hash.A(), hash.B()) {}

inline
Hash64::Hash64(const void* data, size_t length) {
	CRC64 func;
	func.update((const char*)data, length);
	value = func.get();
}

inline
Hash64::Hash64(const Hash64& A, const Hash64& B) {
	CRC64 func;
	func.update(A);
	func.update(B);
	value = func.get();
}

inline
Hash64 Hash64::rand() {
	return Hash64(rand64());
}

inline
std::string Hash64::to_string() const {
	return vnx::to_string(value);
}

inline
std::string Hash64::to_hex_string() const {
	return vnx::to_hex_string(value);
}


inline
void read(TypeInput& in, Hash64& value, const TypeCode* type_code, const uint16_t* code) {
	if(code) {
		switch(code[0]) {
			case CODE_ARRAY:
				if(code[2] == CODE_UINT64) {
					switch(code[1]) {
						case 2: {
							Hash128 hash;
							read(in, hash, type_code, code);
							value = Hash64(hash);
							return;
						}
					}
				}
				break;
			case CODE_ALT_ARRAY:
				if(code[2] == CODE_ALT_UINT64) {
					switch(code[1]) {
						case 0x200: {
							Hash128 hash;
							read(in, hash, type_code, code);
							value = Hash64(hash);
							return;
						}
					}
				}
				break;
		}
	}
	read(in, value.value, type_code, code);
}

inline
void write(TypeOutput& out, const Hash64& value, const TypeCode* type_code, const uint16_t* code) {
	write(out, value.value, type_code, code);
}

inline
void read(std::istream& in, Hash64& value) {
	read(in, value.value);
}

inline
void write(std::ostream& out, const Hash64& value) {
	write(out, value.value);
}

inline
void accept(Visitor& visitor, const Hash64& value) {
	visitor.visit(value.value);
}


} // vnx

#endif /* INCLUDE_VNX_HASH64_HPP_ */

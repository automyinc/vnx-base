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

#ifndef INCLUDE_VNX_HASH128_HPP_
#define INCLUDE_VNX_HASH128_HPP_

#include <vnx/package.hxx>
#include <vnx/Hash128.h>
#include <vnx/Hash64.h>
#include <vnx/Util.h>
#include <vnx/Input.hpp>
#include <vnx/Output.hpp>
#include <vnx/Visitor.h>
#include <vnx/CRC64.h>


namespace vnx {

inline
Hash128::Hash128(const void* data, size_t length) {
	{
		CRC64 func(0xC96C5795D7870F42ull);
		func.update((const char*)data, length);
		A() = Hash64(func.get());
	}
	{
		CRC64 func(~0xC96C5795D7870F42ull);
		func.update((const char*)data, length);
		B() = Hash64(func.get());
	}
}

inline
Hash128::Hash128(const std::string& str) : Hash128(str.data(), str.size()) {}

inline
std::string Hash128::to_string() const {
	return vnx::to_string(*this);
}

inline
std::string Hash128::to_hex_string() const {
	return vnx::to_hex_string(A()) + vnx::to_hex_string(B());
}

inline
std::ostream& operator<<(std::ostream& out, const Hash128& value) {
	vnx::write(out, value);
	return out;
}

inline
std::istream& operator>>(std::istream& in, Hash128& value) {
	vnx::read(in, value);
	return in;
}


inline
void read(TypeInput& in, Hash128& value, const TypeCode* type_code, const uint16_t* code) {
	if(code) {
		switch(code[0]) {
			case CODE_UINT64: {
				Hash64 hash;
				read(in, hash);
				value = Hash128(hash);
				return;
			}
			case CODE_ALT_UINT64: {
				Hash64 hash;
				read(in, hash);
				value = Hash128(flip_bytes(hash));
				return;
			}
		}
	}
	read(in, (std::array<Hash64, 2>&)value, type_code, code);
}

inline
void write(TypeOutput& out, const Hash128& value, const TypeCode* type_code, const uint16_t* code) {
	write(out, (const std::array<Hash64, 2>&)value, type_code, code);
}

inline
void read(std::istream& in, Hash128& value) {
	read(in, (std::array<Hash64, 2>&)value);
}

inline
void write(std::ostream& out, const Hash128& value) {
	write(out, (const std::array<Hash64, 2>&)value);
}

inline
void accept(Visitor& visitor, const Hash128& value) {
	accept(visitor, (const std::array<Hash64, 2>&)value);
}


} // vnx

#endif /* INCLUDE_VNX_HASH128_HPP_ */

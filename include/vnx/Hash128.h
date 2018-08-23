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

#ifndef INCLUDE_VNX_HASH128_H
#define INCLUDE_VNX_HASH128_H

#include <vnx/Hash64.h>

#include <array>


namespace vnx {

class Hash128 : public std::array<Hash64, 2> {
public:
	Hash128() : Hash128(Hash64(), Hash64()) {}
	
	Hash128(const Hash128&) = default;
	
	explicit Hash128(const Hash64& A) {
		(*this)[0] = A;
		(*this)[1] = Hash64(~A);
	}
	
	Hash128(const Hash64& A, const Hash64& B) {
		(*this)[0] = A;
		(*this)[1] = B;
	}
	
	Hash128(const void* data, size_t length);
	
	explicit Hash128(const std::string& str);
	
	static Hash128 rand();
	
	Hash64& A() { return (*this)[0]; }
	Hash64& B() { return (*this)[1]; }
	
	const Hash64& A() const { return (*this)[0]; }
	const Hash64& B() const { return (*this)[1]; }
	
	Hash128& operator=(const Hash128&) = default;
	
	bool operator==(const Hash128& other) const;
	
	bool operator!=(const Hash128& other) const;
	
	std::string to_string();
	
	friend std::ostream& operator<<(std::ostream& out, const Hash128& value);
	
	friend std::istream& operator>>(std::istream& in, Hash128& value);
	
};


inline Hash128 Hash128::rand() {
	return Hash128(Hash64::rand(), Hash64::rand());
}

inline bool Hash128::operator==(const Hash128& other) const {
	return A() == other.A() && B() == other.B();
}

inline bool Hash128::operator!=(const Hash128& other) const {
	return A() != other.A() || B() != other.B();
}


} // vnx


namespace std {
	template<> struct hash<vnx::Hash128> {
		size_t operator()(const vnx::Hash128& x) const {
			return x.A() xor x.B();
		}
	};
} // std

#endif // INCLUDE_VNX_HASH128_H

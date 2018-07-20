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

#ifndef INCLUDE_VNX_HASH64_H_
#define INCLUDE_VNX_HASH64_H_

#include <vnx/CRC64.h>

#include <string.h>
#include <string>


namespace vnx {

class Hash64 {
public:
	Hash64() : value(0) {}
	
	explicit Hash64(const std::string& name);
	
	explicit Hash64(uint64_t hash) : value(hash) {}
	
	static Hash64 rand();
	
	operator uint64_t() const {
		return value;
	}
	
	bool operator==(const std::string& str) const;
	
	bool operator!=(const std::string& str) const;
	
	uint64_t value;
	
};


inline Hash64 hash64(const char* str) {
	CRC64 func;
	func.update(str, strlen(str));
	return Hash64(func.get());
}

inline Hash64 hash64(const std::string& str) {
	CRC64 func;
	func.update(str.c_str(), str.size());
	return Hash64(func.get());
}

inline Hash64 hash64(const char* buf, size_t len) {
	CRC64 func;
	func.update(buf, len);
	return Hash64(func.get());
}


inline Hash64::Hash64(const std::string& name) : value(hash64(name)) {}

inline bool Hash64::operator==(const std::string& str) const {
	return value == hash64(str);
}

inline bool Hash64::operator!=(const std::string& str) const {
	return value != hash64(str);
}


} // vnx


namespace std {
	template<> struct hash<vnx::Hash64> {
		size_t operator()(const vnx::Hash64& x) const {
			return x.value;
		}
	};
} // std


#endif /* INCLUDE_VNX_HASH64_H_ */

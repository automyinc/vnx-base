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

#ifndef INCLUDE_VNX_UTIL_H_
#define INCLUDE_VNX_UTIL_H_

#include <string>
#include <vector>
#include <algorithm>

#include <stdint.h>


namespace vnx {

/// Substitudes any occurrence of \p from with \p to and returns the resulting string.
std::string string_subs(std::string str, const std::string& from, const std::string& to);

/** \brief Split string into multiple parts based on special char \p sep.
 * 
 * An empty input string results in a vector of size 1 with an empty string as the only element.
 *
 * Set \p clean to true to not get any empty strings. This can be useful if \p sep occurs
 * multiple times in a row and empty array elements are unwanted.
 * In that case, an empty input string results in an empty vector.
 */
std::vector<std::string> string_split(const std::string& str, char sep, bool clean = false);

/// Returns a very good 64-bit random number. (Initialized with nano-second timestamp)
uint64_t rand64();

/// Converts an integer to a hex string efficiently. (Without leading "0x")
template<typename T>
std::string to_hex_string(const T& value) {
	static const char map[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
	std::string str;
	str.resize(sizeof(T) * 2);
	auto p_value = (const uint8_t*)(&value);
	for(size_t i = 0; i < sizeof(T); ++i) {
		str[(sizeof(T) - i - 1) * 2] = map[(p_value[i] & 0xF0) >> 4];
		str[(sizeof(T) - i - 1) * 2 + 1] = map[p_value[i] & 0x0F];
	}
	return str;
}

/// Converts ASCII string to lower case
inline
std::string ascii_tolower(std::string str)
{
	std::transform(str.begin(), str.end(), str.begin(), [](char c){ return std::tolower(c); });
	return str;
}


/// Expects one line of input from the user with echoing disabled. During input, process log output is paused.
std::string input_password(const std::string &prompt="");


} // vnx

#endif /* INCLUDE_VNX_UTIL_H_ */

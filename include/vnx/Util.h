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

#include <stdint.h>


namespace vnx {

/*
 * Substitudes any occurence of "from" with "to" and returns the resulting string.
 */
std::string string_subs(std::string str, const std::string& from, const std::string& to);

/*
 * Split string into multiple parts based on special char "sep".
 * An empty input string results in a vector of size 1 with an empty string as the only element.
 */
std::vector<std::string> string_split(std::string str, char sep);

/*
 * Returns a true 64 bit random number.
 */
uint64_t rand64();

/*
 * Converts integers to hex strings efficiently.
 */
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


} // vnx

#endif /* INCLUDE_VNX_UTIL_H_ */

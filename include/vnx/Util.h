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
 */
std::vector<std::string> string_split(std::string str, char sep);

/*
 * Returns a true 64 bit random number.
 */
uint64_t rand64();


} // vnx

#endif /* INCLUDE_VNX_UTIL_H_ */

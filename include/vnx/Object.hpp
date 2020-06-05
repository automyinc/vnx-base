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

#ifndef INCLUDE_VNX_OBJECT_HPP_
#define INCLUDE_VNX_OBJECT_HPP_

#include <vnx/Object.h>
#include <vnx/Input.hpp>
#include <vnx/Output.hpp>


namespace vnx {

inline
std::ostream& operator<<(std::ostream& out, const Object& value) {
	vnx::write(out, value);
	return out;
}

inline
std::istream& operator>>(std::istream& in, Object& value) {
	vnx::read(in, value);
	return in;
}


} // vnx

#endif /* INCLUDE_VNX_OBJECT_HPP_ */

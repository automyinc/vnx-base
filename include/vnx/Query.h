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

#ifndef INCLUDE_VNX_QUERY_H
#define INCLUDE_VNX_QUERY_H

#include <vnx/Value.h>
#include <vnx/Variant.h>


namespace vnx {

void query(const Value& value, const std::string& path, Variant& result);

void query(std::shared_ptr<const Value> value, const std::string& path, Variant& result);

template<typename T>
void query(std::shared_ptr<T> value, const std::string& path, Variant& result) {
	query(std::dynamic_pointer_cast<const Value>(value), path, result);
}

void query(const Variant& value, const std::string& path, Variant& result);


} // vnx

#endif // INCLUDE_VNX_QUERY_H

/*
 * Util.hpp
 *
 *  Created on: Nov 30, 2020
 *      Author: jaw
 */

#ifndef INCLUDE_VNX_UTIL_HPP_
#define INCLUDE_VNX_UTIL_HPP_

#include <vnx/Output.h>
#include <string>


namespace vnx {


template<class T>
std::string string_join(const T &collection, const std::string sep){
	std::string result = "";
	auto iter = collection.begin();
	while(iter != collection.end()){
		result += vnx::to_string_value(*iter);
		iter++;
		if(iter != collection.end()) result += sep;
	}
	return result;
}



} // vnx

#endif /* INCLUDE_VNX_UTIL_HPP_ */

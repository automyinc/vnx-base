/*
 * exception.h
 *
 *  Created on: Apr 5, 2020
 *      Author: mad
 */

#ifndef INCLUDE_VNX_EXCEPTION_H_
#define INCLUDE_VNX_EXCEPTION_H_

#include <vnx/Exception.hxx>

#include <stdexcept>


namespace vnx {

class exception : public std::exception {
public:
	exception() = default;
	
	exception(std::shared_ptr<const Exception> value)
		:	value_(value)
	{
		if(value) {
			what_ = value->to_string();
		}
	}
	
	std::shared_ptr<const Exception> value() const {
		return value_;
	}
	
	const char* what() const noexcept override {
		return what_.c_str();
	}
	
private:
	std::shared_ptr<const Exception> value_;
	
	std::string what_;
	
};


} // vnx

#endif /* INCLUDE_VNX_EXCEPTION_H_ */

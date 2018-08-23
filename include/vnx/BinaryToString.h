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

#ifndef INCLUDE_VNX_BINARYTOSTRING_H
#define INCLUDE_VNX_BINARYTOSTRING_H

#include <vnx/DefaultPrinter.h>

#include <sstream>


namespace vnx {

class BinaryToString : public DefaultPrinter {
public:
	BinaryToString() : DefaultPrinter(stream) {}
	
	std::string str() const {
		return stream.str();
	}
	
	void visit(const std::string& value) override {
		if(!stack) {
			stream << value;
		} else {
			DefaultPrinter::visit(value);
		}
	}
	
	void enum_value(uint32_t value, const std::string& name) override {
		if(!stack) {
			stream << name;
		} else {
			DefaultPrinter::enum_value(value, name);
		}
	}
	
protected:
	std::ostringstream stream;
	
};


} // vnx

#endif // INCLUDE_VNX_BINARYTOSTRING_H

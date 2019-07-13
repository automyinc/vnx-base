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

#ifndef INCLUDE_VNX_VALUE_H_
#define INCLUDE_VNX_VALUE_H_

#include <vnx/Type.h>
#include <vnx/Visitor.h>


namespace vnx {

/** \brief Base class for any VNI interface class.
 * 
 * Value provides a polymorph interface to the type system.
 */
class Value {
public:
	virtual ~Value() {}
	
	virtual vnx::Hash64 get_type_hash() const = 0;
	virtual const char* get_type_name() const = 0;
	
	static std::shared_ptr<Value> create() { return 0; }
	virtual std::shared_ptr<Value> clone() const = 0;
	
	virtual void read(TypeInput& in, const TypeCode* type_code, const uint16_t* code) = 0;
	virtual void write(TypeOutput& out, const TypeCode* type_code, const uint16_t* code) const = 0;
	
	virtual void read(std::istream& in) = 0;
	virtual void write(std::ostream& out) const = 0;
	
	virtual void accept(Visitor& visitor) const = 0;
	
	virtual Object to_object() const = 0;
	virtual void from_object(const Object& object) = 0;
	
	std::string to_string() const;
	void from_string(const std::string& str);
	
	friend std::ostream& operator<<(std::ostream& _out, const Value& _value);
	friend std::istream& operator>>(std::istream& _in, Value& _value);
	
};


/// Creates new Value with given type hash
std::shared_ptr<Value> create(Hash64 hash);

/// Creates new Value with given type time
std::shared_ptr<Value> create(const std::string& type_name);

/// Reads a Value from the stream
void read(std::istream& in, Value& value);

template<typename T>
std::shared_ptr<T> clone(const std::shared_ptr<T>& value) {
	if(value) {
		return std::dynamic_pointer_cast<T>(value->clone());
	}
	return 0;
}

template<typename T>
std::shared_ptr<T> clone(const std::shared_ptr<const T>& value) {
	if(value) {
		return std::dynamic_pointer_cast<T>(value->clone());
	}
	return 0;
}

template<typename T>
std::shared_ptr<T> clone(const T& value) {
	return std::dynamic_pointer_cast<T>(value.clone());
}


} // vnx

#endif /* INCLUDE_VNX_VALUE_H_ */

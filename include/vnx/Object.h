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

#ifndef INCLUDE_VNX_OBJECT_H
#define INCLUDE_VNX_OBJECT_H

#include <vnx/package.hxx>
#include <vnx/Value.h>
#include <vnx/Variant.h>


namespace vnx {

/** \brief A dynamically typed object consisting of a map of Variant fields.
 * 
 * Object can be used to hold dynamically typed data when creating a VNI definition
 * and generating code is not possible or when performance is not an issue.
 */
class Object : public Value {
public:
	std::map<std::string, Variant> field;		///< Data fields (name => value)
	
	/// Returns reference to field value
	Variant& operator[](const std::string& name) {
		return field[name];
	}
	
	/// Returns reference to field value
	const Variant& operator[](const std::string& name) const {
		auto iter = field.find(name);
		if(iter != field.end()) {
			return iter->second;
		}
		return Variant::get_empty();
	}
	
	bool empty() const {
		return field.empty();
	}
	
	void clear() {
		field.clear();
	}
	
	Hash64 get_type_hash() const override {
		return Hash64(get_type_name());
	}
	
	const char* get_type_name() const override {
		return "vnx.Object";
	}
	
	static std::shared_ptr<Object> create() {
		return std::make_shared<Object>();
	}
	
	std::shared_ptr<Value> clone() const override {
		return std::make_shared<Object>(*this);
	}
	
	void read(TypeInput& in, const TypeCode* type_code, const uint16_t* code) override {
		vnx::read(in, *this, type_code, code);
	}
	
	void write(TypeOutput& out, const TypeCode* type_code, const uint16_t* code) const override {
		vnx::write(out, *this, type_code, code);
	}
	
	void read(std::istream& in) override {
		vnx::read(in, *this);
	}
	
	void write(std::ostream& out) const override {
		vnx::write(out, *this);
	}
	
	void accept(Visitor& visitor) const override {
		vnx::accept(visitor, *this);
	}
	
	Object to_object() const override {
		return *this;
	}
	
	void from_object(const Object& object) override {
		*this = object;
	}
	
	friend std::ostream& operator<<(std::ostream& out, const Object& value) {
		vnx::write(out, value);
		return out;
	}
	
	friend std::istream& operator>>(std::istream& in, Object& value) {
		vnx::read(in, value);
		return in;
	}
	
	static const uint16_t CODE[];
	static const uint16_t ALT_CODE[];
	
};


} // vnx

#endif // INCLUDE_VNX_OBJECT_H

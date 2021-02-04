
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_vnx_Tuple_HXX_
#define INCLUDE_vnx_Tuple_HXX_

#include <vnx/package.hxx>
#include <vnx/Value.h>
#include <vnx/Variant.hpp>


namespace vnx {

class Tuple : public ::vnx::Value {
public:
	
	std::vector<::vnx::Variant> fields;
	
	typedef ::vnx::Value Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xd0f5f12fbf08b4b1ull;
	
	vnx::Hash64 get_type_hash() const override;
	std::string get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	virtual ::vnx::Variant get_field_by_index(const uint32_t& index) const;
	virtual void set_field_by_index(const uint32_t& index, const ::vnx::Variant& value);
	virtual uint32_t get_num_fields() const;
	
	static std::shared_ptr<Tuple> create();
	std::shared_ptr<vnx::Value> clone() const override;
	
	void read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code) override;
	void write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const override;
	
	void read(std::istream& _in) override;
	void write(std::ostream& _out) const override;
	
	void accept(vnx::Visitor& _visitor) const override;
	
	vnx::Object to_object() const override;
	void from_object(const vnx::Object& object) override;
	
	vnx::Variant get_field(const std::string& name) const override;
	void set_field(const std::string& name, const vnx::Variant& value) override;
	
	friend std::ostream& operator<<(std::ostream& _out, const Tuple& _value);
	friend std::istream& operator>>(std::istream& _in, Tuple& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};


} // namespace vnx


namespace vnx {

} // vnx

#endif // INCLUDE_vnx_Tuple_HXX_


// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_vnx_record_index_entry_t_HXX_
#define INCLUDE_vnx_record_index_entry_t_HXX_

#include <vnx/Type.h>
#include <vnx/package.hxx>


namespace vnx {

struct record_index_entry_t {
	
	
	int64_t pos = -1;
	int64_t time = 0;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0x84d2685378679269ull;
	
	vnx::Hash64 get_type_hash() const;
	std::string get_type_name() const;
	const vnx::TypeCode* get_type_code() const;
	
	static std::shared_ptr<record_index_entry_t> create();
	std::shared_ptr<record_index_entry_t> clone() const;
	
	void read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code);
	void write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const;
	
	void read(std::istream& _in);
	void write(std::ostream& _out) const;
	
	void accept(vnx::Visitor& _visitor) const;
	
	vnx::Object to_object() const;
	void from_object(const vnx::Object& object);
	
	vnx::Variant get_field(const std::string& name) const;
	void set_field(const std::string& name, const vnx::Variant& value);
	
	friend std::ostream& operator<<(std::ostream& _out, const record_index_entry_t& _value);
	friend std::istream& operator>>(std::istream& _in, record_index_entry_t& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};


} // namespace vnx


namespace vnx {

template<>
struct is_equivalent<::vnx::record_index_entry_t> {
	bool operator()(const uint16_t* code, const TypeCode* type_code);
};

} // vnx

#endif // INCLUDE_vnx_record_index_entry_t_HXX_

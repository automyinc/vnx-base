
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_vnx_Player_seek_to_position_HXX_
#define INCLUDE_vnx_Player_seek_to_position_HXX_

#include <vnx/package.hxx>
#include <vnx/Value.h>


namespace vnx {

class Player_seek_to_position : public ::vnx::Value {
public:
	
	vnx::float64_t position = 0;
	
	typedef ::vnx::Value Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	vnx::Hash64 get_type_hash() const override;
	const char* get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	static std::shared_ptr<Player_seek_to_position> create();
	std::shared_ptr<vnx::Value> clone() const;
	
	void read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code);
	void write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const;
	
	void read(std::istream& _in);
	void write(std::ostream& _out) const;
	
	void accept(vnx::Visitor& _visitor) const;
	
	vnx::Object to_object() const;
	void from_object(const vnx::Object& object);
	
	friend std::ostream& operator<<(std::ostream& _out, const Player_seek_to_position& _value);
	friend std::istream& operator>>(std::istream& _in, Player_seek_to_position& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};


} // namespace vnx

#endif // INCLUDE_vnx_Player_seek_to_position_HXX_

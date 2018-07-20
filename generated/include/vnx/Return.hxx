
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_vnx_Return_HXX_
#define INCLUDE_vnx_Return_HXX_

#include <vnx/package.hxx>
#include <vnx/Hash64.h>
#include <vnx/Message.hxx>
#include <vnx/Request.hxx>
#include <vnx/Value.h>


namespace vnx {

class Return : public ::vnx::Message {
public:
	
	::uint64_t request_id = 0;
	::vnx::Hash64 src_mac;
	::std::shared_ptr<const ::vnx::Value> value;
	
	typedef ::vnx::Message Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	vnx::Hash64 get_type_hash() const;
	const char* get_type_name() const;
	
	static ::std::shared_ptr<::vnx::Return> create_no_such_service_return(const ::std::shared_ptr<const ::vnx::Request>& request);
	
	static std::shared_ptr<Return> create();
	std::shared_ptr<vnx::Value> clone() const;
	
	void read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code);
	void write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const;
	
	void read(std::istream& _in);
	void write(std::ostream& _out) const;
	
	void accept(vnx::Visitor& _visitor) const;
	
	friend std::ostream& operator<<(std::ostream& _out, const Return& _value);
	friend std::istream& operator>>(std::istream& _in, Return& _value);
	
	static const vnx::TypeCode* get_type_code();
	static std::shared_ptr<vnx::TypeCode> create_type_code();
	
};


} // namespace vnx

#endif // INCLUDE_vnx_Return_HXX_
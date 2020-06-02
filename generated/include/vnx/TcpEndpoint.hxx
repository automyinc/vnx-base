
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_vnx_TcpEndpoint_HXX_
#define INCLUDE_vnx_TcpEndpoint_HXX_

#include <vnx/package.hxx>
#include <vnx/Endpoint.hxx>


namespace vnx {

class TcpEndpoint : public ::vnx::Endpoint {
public:
	static const int32_t default_port = 4444;
	
	std::string host_name;
	int32_t port = 0;
	vnx::bool_t reuse_addr = true;
	vnx::bool_t tcp_no_delay = true;
	vnx::bool_t tcp_keepalive = true;
	
	typedef ::vnx::Endpoint Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	vnx::Hash64 get_type_hash() const override;
	const char* get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	static std::shared_ptr<const ::vnx::TcpEndpoint> create(const std::string& host_name, const int32_t& port);
	static std::shared_ptr<const ::vnx::TcpEndpoint> from_url(const std::string& url);
	virtual int32_t open() const;
	virtual void bind(const int32_t& socket) const;
	virtual void connect(const int32_t& socket) const;
	virtual void listen(const int32_t& socket) const;
	virtual int32_t accept(const int32_t& socket) const;
	virtual std::string to_url() const;
	
	static std::shared_ptr<TcpEndpoint> create();
	std::shared_ptr<vnx::Value> clone() const;
	
	void read(vnx::TypeInput& _in, const vnx::TypeCode* _type_code, const uint16_t* _code);
	void write(vnx::TypeOutput& _out, const vnx::TypeCode* _type_code, const uint16_t* _code) const;
	
	void read(std::istream& _in);
	void write(std::ostream& _out) const;
	
	void accept(vnx::Visitor& _visitor) const;
	
	vnx::Object to_object() const;
	void from_object(const vnx::Object& object);
	
	friend std::ostream& operator<<(std::ostream& _out, const TcpEndpoint& _value);
	friend std::istream& operator>>(std::istream& _in, TcpEndpoint& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
};


} // namespace vnx

#endif // INCLUDE_vnx_TcpEndpoint_HXX_

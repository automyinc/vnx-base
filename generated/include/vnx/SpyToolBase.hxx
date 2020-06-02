
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_vnx_SpyToolBase_HXX_
#define INCLUDE_vnx_SpyToolBase_HXX_

#include <vnx/package.hxx>
#include <vnx/Hash64.h>
#include <vnx/Module.h>
#include <vnx/TopicInfoList.hxx>


namespace vnx {

class SpyToolBase : public ::vnx::Module {
public:
	
	std::string proxy_name;
	std::string topic_expr;
	vnx::bool_t only_once = false;
	vnx::bool_t header_only = false;
	vnx::bool_t pretty_print = true;
	int32_t max_list_size = 1000;
	int32_t max_queue_ms = 100;
	::vnx::Hash64 receive_tunnel;
	
	typedef ::vnx::Module Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	SpyToolBase(const std::string& _vnx_name);
	
	vnx::Hash64 get_type_hash() const;
	const char* get_type_name() const;
	const vnx::TypeCode* get_type_code() const;
	
	void read(std::istream& _in);
	void write(std::ostream& _out) const;
	
	void accept(vnx::Visitor& _visitor) const;
	
	vnx::Object to_object() const;
	void from_object(const vnx::Object& object);
	
	friend std::ostream& operator<<(std::ostream& _out, const SpyToolBase& _value);
	friend std::istream& operator>>(std::istream& _in, SpyToolBase& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
protected:
	virtual void handle(std::shared_ptr<const ::vnx::TopicInfoList> _value, std::shared_ptr<const vnx::Sample> _sample) { handle(_value); }
	virtual void handle(std::shared_ptr<const ::vnx::TopicInfoList> _value) {}
	
	void vnx_handle_switch(std::shared_ptr<const vnx::Sample> _sample) override;
	std::shared_ptr<vnx::Value> vnx_call_switch(std::shared_ptr<const vnx::Value> _value, const vnx::request_id_t& _request_id) override;
	
private:
	
};


} // namespace vnx

#endif // INCLUDE_vnx_SpyToolBase_HXX_

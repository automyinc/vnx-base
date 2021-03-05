
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_vnx_BaseProxyBase_HXX_
#define INCLUDE_vnx_BaseProxyBase_HXX_

#include <vnx/package.hxx>
#include <vnx/Hash64.hpp>
#include <vnx/Module.h>
#include <vnx/Session.hxx>
#include <vnx/TopicPtr.hpp>


namespace vnx {

class BaseProxyBase : public ::vnx::Module {
public:
	
	std::string address;
	std::vector<::vnx::TopicPtr> import_list;
	std::vector<::vnx::TopicPtr> export_list;
	std::vector<std::string> forward_list;
	std::vector<::vnx::Hash64> tunnel_list;
	std::map<::vnx::TopicPtr, ::vnx::TopicPtr> import_map;
	std::map<::vnx::TopicPtr, ::vnx::TopicPtr> export_map;
	::vnx::Hash64 receive_tunnel;
	::vnx::Hash64 request_tunnel;
	vnx::bool_t auto_import = false;
	vnx::bool_t time_sync = false;
	vnx::bool_t use_authentication = false;
	vnx::bool_t block_until_connect = true;
	vnx::bool_t block_until_reconnect = false;
	int32_t max_queue_ms = 100;
	int32_t max_queue_size = 1000;
	int32_t max_hop_count = 10;
	int32_t recv_buffer_size = 0;
	int32_t send_buffer_size = 131072;
	std::string default_access = "DEFAULT";
	
	typedef ::vnx::Module Super;
	
	static const vnx::Hash64 VNX_TYPE_HASH;
	static const vnx::Hash64 VNX_CODE_HASH;
	
	static constexpr uint64_t VNX_TYPE_ID = 0xd8241ff9082104f5ull;
	
	BaseProxyBase(const std::string& _vnx_name);
	
	vnx::Hash64 get_type_hash() const override;
	std::string get_type_name() const override;
	const vnx::TypeCode* get_type_code() const override;
	
	void read(std::istream& _in) override;
	void write(std::ostream& _out) const override;
	
	void accept(vnx::Visitor& _visitor) const override;
	
	vnx::Object to_object() const override;
	void from_object(const vnx::Object& object) override;
	
	vnx::Variant get_field(const std::string& name) const override;
	void set_field(const std::string& name, const vnx::Variant& value) override;
	
	friend std::ostream& operator<<(std::ostream& _out, const BaseProxyBase& _value);
	friend std::istream& operator>>(std::istream& _in, BaseProxyBase& _value);
	
	static const vnx::TypeCode* static_get_type_code();
	static std::shared_ptr<vnx::TypeCode> static_create_type_code();
	
protected:
	using Super::handle;
	
	virtual void login_async(const std::string& name, const std::string& password, const vnx::request_id_t& _request_id) const = 0;
	void login_async_return(const vnx::request_id_t& _request_id, const std::shared_ptr<const ::vnx::Session>& _ret_0) const;
	virtual void enable_import(const std::string& topic_name) = 0;
	virtual void disable_import(const std::string& topic_name) = 0;
	virtual void enable_export(const std::string& topic_name) = 0;
	virtual void disable_export(const std::string& topic_name) = 0;
	virtual void enable_forward(const std::string& service_name, const int32_t& max_queue_ms, const int32_t& max_queue_size) = 0;
	virtual void disable_forward(const std::string& service_name) = 0;
	virtual void enable_tunnel(const ::vnx::Hash64& tunnel_addr, const int32_t& max_queue_ms, const int32_t& max_queue_size) = 0;
	virtual void disable_tunnel(const ::vnx::Hash64& tunnel_addr) = 0;
	virtual void wait_on_connect_async(const vnx::request_id_t& _request_id) const = 0;
	void wait_on_connect_async_return(const vnx::request_id_t& _request_id, const ::vnx::Hash64& _ret_0) const;
	virtual void wait_on_disconnect_async(const vnx::request_id_t& _request_id) const = 0;
	void wait_on_disconnect_async_return(const vnx::request_id_t& _request_id, const ::vnx::Hash64& _ret_0) const;
	virtual void on_connect() = 0;
	virtual void on_disconnect() = 0;
	virtual void on_remote_connect(const ::vnx::Hash64& process_id) = 0;
	virtual void on_login(const std::string& name, const std::string& password) = 0;
	virtual void on_remote_login(std::shared_ptr<const ::vnx::Session> remote_session) = 0;
	
	void vnx_handle_switch(std::shared_ptr<const vnx::Value> _value) override;
	std::shared_ptr<vnx::Value> vnx_call_switch(std::shared_ptr<const vnx::Value> _method, const vnx::request_id_t& _request_id) override;
	
};


} // namespace vnx


namespace vnx {

} // vnx

#endif // INCLUDE_vnx_BaseProxyBase_HXX_


// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_vnx_JRPC_Server_CLIENT_HXX_
#define INCLUDE_vnx_JRPC_Server_CLIENT_HXX_

#include <vnx/Client.h>
#include <vnx/BaseServer.h>


namespace vnx {

class JRPC_ServerClient : public vnx::Client {
public:
	JRPC_ServerClient(const std::string& service_name);
	
	JRPC_ServerClient(vnx::Hash64 service_addr);
	
	::vnx::Object vnx_get_config_object();
	
	::vnx::Variant vnx_get_config(const std::string& name);
	
	void vnx_set_config_object(const ::vnx::Object& config);
	
	void vnx_set_config_object_async(const ::vnx::Object& config);
	
	void vnx_set_config(const std::string& name, const ::vnx::Variant& value);
	
	void vnx_set_config_async(const std::string& name, const ::vnx::Variant& value);
	
	::vnx::TypeCode vnx_get_type_code();
	
	std::shared_ptr<const ::vnx::ModuleInfo> vnx_get_module_info();
	
	void vnx_restart();
	
	void vnx_restart_async();
	
	void vnx_stop();
	
	void vnx_stop_async();
	
	vnx::bool_t vnx_self_test();
	
};


} // namespace vnx

#endif // INCLUDE_vnx_JRPC_Server_CLIENT_HXX_

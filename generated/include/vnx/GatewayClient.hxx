
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_vnx_Gateway_CLIENT_HXX_
#define INCLUDE_vnx_Gateway_CLIENT_HXX_

#include <vnx/Client.h>
#include <vnx/Module.h>
#include <vnx/Request.hxx>


namespace vnx {

class GatewayClient : public vnx::Client {
public:
	GatewayClient(const std::string& service_name);
	
	GatewayClient(vnx::Hash64 service_addr);
	
	::vnx::Object vnx_get_config_object();
	
	::vnx::Variant vnx_get_config(const std::string& name = "");
	
	void vnx_set_config_object(const ::vnx::Object& config = ::vnx::Object());
	
	void vnx_set_config_object_async(const ::vnx::Object& config = ::vnx::Object());
	
	void vnx_set_config(const std::string& name = "", const ::vnx::Variant& value = ::vnx::Variant());
	
	void vnx_set_config_async(const std::string& name = "", const ::vnx::Variant& value = ::vnx::Variant());
	
	::vnx::TypeCode vnx_get_type_code();
	
	std::shared_ptr<const ::vnx::ModuleInfo> vnx_get_module_info();
	
	void vnx_restart();
	
	void vnx_restart_async();
	
	void vnx_stop();
	
	void vnx_stop_async();
	
	vnx::bool_t vnx_self_test();
	
	void forward(std::shared_ptr<const ::vnx::Request> request = nullptr);
	
	void forward_async(std::shared_ptr<const ::vnx::Request> request = nullptr);
	
};


} // namespace vnx

#endif // INCLUDE_vnx_Gateway_CLIENT_HXX_

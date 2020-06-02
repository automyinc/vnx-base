
// AUTO GENERATED by vnxcppcodegen

#ifndef INCLUDE_vnx_SpyTool_ASYNC_CLIENT_HXX_
#define INCLUDE_vnx_SpyTool_ASYNC_CLIENT_HXX_

#include <vnx/AsyncClient.h>
#include <vnx/Hash64.h>
#include <vnx/Module.h>
#include <vnx/TopicInfoList.hxx>


namespace vnx {

class SpyToolAsyncClient : public vnx::AsyncClient {
public:
	SpyToolAsyncClient(const std::string& service_name);
	
	SpyToolAsyncClient(vnx::Hash64 service_addr);
	
	std::vector<uint64_t> vnx_get_pending_ids() const override;
	
protected:
	void vnx_purge_request(uint64_t _request_id) override;
	
	void vnx_callback_switch(uint64_t _request_id, std::shared_ptr<const vnx::Value> _value) override;
	
private:
	
};


} // namespace vnx

#endif // INCLUDE_vnx_SpyTool_ASYNC_CLIENT_HXX_

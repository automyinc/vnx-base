 /*************************************************************************
 *
 *  [2017] - [2018] Automy Inc.
 *  All Rights Reserved.
 *
 * NOTICE:  All information contained herein is, and remains
 * the property of Automy Incorporated and its suppliers,
 * if any.  The intellectual and technical concepts contained
 * herein are proprietary to Automy Incorporated
 * and its suppliers and may be covered by U.S. and Foreign Patents,
 * patents in process, and are protected by trade secret or copyright law.
 * Dissemination of this information or reproduction of this material
 * is strictly forbidden unless prior written permission is obtained
 * from Automy Incorporated.
 */

#ifndef INCLUDE_VNX_GENERICASYNCCLIENT_H_
#define INCLUDE_VNX_GENERICASYNCCLIENT_H_

#include <vnx/ModuleInterfaceAsyncClient.hxx>
#include <vnx/Object.h>


namespace vnx {

class GenericAsyncClient : public ModuleInterfaceAsyncClient {
public:
	GenericAsyncClient(const std::string& service_name);

	GenericAsyncClient(vnx::Hash64 service_addr);

	uint64_t call(	const std::string& method, const Object& args,
					const std::function<void(std::shared_ptr<const Value>)>& _callback = std::function<void(std::shared_ptr<const Value>)>(),
					const std::function<void(const std::exception&)>& _error_callback = std::function<void(const std::exception&)>());

	std::vector<uint64_t> vnx_get_pending_ids() const override;

protected:
	void vnx_purge_request(uint64_t _request_id, const std::exception& _ex) override;

	void vnx_callback_switch(uint64_t _request_id, std::shared_ptr<const vnx::Value> _value) override;

private:
	std::map<uint64_t, std::pair<std::function<void(std::shared_ptr<const Value>)>,
			std::function<void(const std::exception&)>>> vnx_queue_generic;

};


} // vnx

#endif /* INCLUDE_VNX_GENERICASYNCCLIENT_H_ */

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

#ifndef INCLUDE_VNX_PROXY_H_
#define INCLUDE_VNX_PROXY_H_

#include <vnx/ProxyBase.hxx>
#include <vnx/Endpoint.hxx>


namespace vnx {


class Proxy : public ProxyBase {
public:
	/** \brief Create new Proxy instance.
	 * 
	 * @param name_ Name of the module
	 * @param endpoint_ Endpoint to connect to and re-connect in case of failure, optional
	 * @param socket_ Already connected socket, optional
	 */
	Proxy(const std::string& name_, std::shared_ptr<const Endpoint> endpoint_ = 0, int socket_ = -1);

protected:
	bool handle(std::shared_ptr<const Return> result) override;

	void handle(std::shared_ptr<const FlowMessage> flow_msg) override;

private:
	void send_outgoing(std::shared_ptr<const Sample> sample) override;

	void send_outgoing(std::shared_ptr<const Request> request, const Hash64 &original_dst_mac) override;

	void clear_outputs() override;

	void read_socket_until_error(std::shared_ptr<Pipe> service_pipe) override;

	void disconnect_cleanup() override;

	using Super::process; // brings the other overloads into scope

	void process(std::shared_ptr<FlowMessage> flow_msg) noexcept;

	TypeOutput out;
	std::unordered_map<Hash128, uint64_t> channel_map;				// [(src_mac, topic) => seq_num]

};


} // vnx

#endif /* INCLUDE_VNX_PROXY_H_ */

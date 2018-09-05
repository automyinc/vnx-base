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
#include <vnx/ProxyClient.hxx>
#include <vnx/Endpoint.hxx>
#include <vnx/TimeServer.h>

#include <atomic>


namespace vnx {

class Proxy : public ProxyBase {
public:
	Proxy(const std::string& name_, std::shared_ptr<const Endpoint> endpoint_ = 0, int socket_ = -1);
	
protected:
	void init() override;
	
	void main() override;
	
	void handle(std::shared_ptr<const Message> msg) override;
	
	void handle(std::shared_ptr<const Sample> sample) override;
	
	std::shared_ptr<const Return> handle(std::shared_ptr<const Request> request) override;
	
	void enable_import(const std::string& topic_name) override;
	
	void disable_import(const std::string& topic_name) override;
	
	void enable_export(const std::string& topic_name) override;
	
	void disable_export(const std::string& topic_name) override;
	
	void enable_forward(const std::string& service_name, const int32_t& max_queue_ms) override;
	
	void disable_forward(const std::string& service_name) override;
	
	void enable_tunnel(const Hash64& tunnel_addr, const std::string& serive_name, const int32_t& max_queue_ms) override;
	
	void disable_tunnel(const Hash64& tunnel_addr) override;
	
	void on_connect() override;
	
	void on_disconnect() override;
	
	void handle(std::shared_ptr<const TopicInfoList> value, std::shared_ptr<const Sample> sample) override;
	
private:
	void enable_forward(const Hash64& serive_addr, const int32_t& max_queue_ms);
	
	void disable_forward(const Hash64& serive_addr);
	
	void update_topics();
	
	void print_stats();
	
	void read_loop(std::shared_ptr<const Endpoint> endpoint);
	
private:
	Hash64 internal_addr;
	Hash64 service_addr;
	std::shared_ptr<const Endpoint> endpoint;
	
	std::unordered_map<std::string, uint64_t> import_table;
	std::unordered_map<Hash64, uint64_t> forward_table;
	std::unordered_map<Hash64, Hash64> tunnel_hash_map;
	std::vector<std::shared_ptr<Pipe>> resume_list;
	
	std::shared_ptr<ProxyClient> remote;
	std::shared_ptr<const TopicInfoList> topic_info;
	Handle<TimeServer> time_server;
	
	bool is_connected = false;
	SocketOutputStream stream_out;
	std::ostringstream str_stream_out;
	TypeOutput out;
	
	std::atomic<int64_t> num_samples_send;
	std::atomic<int64_t> num_samples_recv;
	std::atomic<int64_t> num_requests_send;
	std::atomic<int64_t> num_requests_recv;
	
	// all below shared via mutex
	std::mutex mutex;
	int socket = -1;
	std::unordered_map<uint64_t, std::shared_ptr<const Request>> request_map;
	
};


} // vnx

#endif /* INCLUDE_VNX_PROXY_H_ */

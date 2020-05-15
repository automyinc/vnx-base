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

/** \brief Module to connect to other processes.
 * 
 * Configuration options:
 * - \b address URL to connect to, in case given \p endpoint_ == null.
 * 		For example: "hostname" (on default port 4444), "hostname:1234" or "domain.sock".
 * - \b import_list Topics to import (ie. subscribe to) from other process.
 * - \b export_list Topics to forward to other process without them asking for it.
 * - \b forward_list Services to import (ie. forward requests to) from other process.
 * - \b tunnel_map Service tunnel map, similar to forward_list, except with a local alias (the key).
 * 		For example Hash64("other.vnx.process") => "vnx.process".
 * - \b receive_tunnel Optional tunnel pipe to forward all received samples to, instead of the local process.
 * - \b request_tunnel Optional tunnel pipe to forward all received requests to, instead of the local process.
 * - \b auto_import Flag if to automatically import all topics which are subscribed to in the local process.
 * 		(dangerous, can easily cause loops, use only if local process does not export any topics)
 * - \b time_sync Flag if to synchronize our time with the other process.
 * - \b max_queue_ms Maximum default queue length when not otherwise specified.
 * - \b max_hop_count Maximum hop count for received messages, used to defuse loops.
 */
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
	void init() override;
	
	void main() override;
	
	void handle(std::shared_ptr<const Message> message) override;
	
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
	
	void on_remote_connect(const Hash64& process_id) override;
	
private:
	void enable_forward(const Hash64& serive_addr, const int32_t& max_queue_ms);
	
	void disable_forward(const Hash64& serive_addr);
	
	void update_topics();
	
	void print_stats();
	
	// to be called by read_loop() only
	std::shared_ptr<Pipe> add_return_pipe(Hash64 src_mac, std::shared_ptr<Pipe> pipe = 0);
	
	void read_loop(std::shared_ptr<const Endpoint> endpoint);
	
private:
	Hash64 service_addr;
	Hash64 public_service_addr;
	Hash64 remote_addr;
	Hash64 remote_tunnel_addr;
	std::shared_ptr<const Endpoint> endpoint;
	
	std::unordered_map<std::string, uint64_t> import_table;
	std::unordered_map<Hash64, uint64_t> forward_table;
	std::unordered_map<Hash64, Hash64> tunnel_hash_map;
	std::vector<std::shared_ptr<Pipe>> resume_list;
	std::set<std::pair<Hash64, Hash64>> outgoing;
	
	std::shared_ptr<ProxyClient> remote;
	std::shared_ptr<const TopicInfoList> topic_info;
	Handle<TimeServer> time_server;
	
	bool is_connected = false;
	SocketOutputStream stream_out;
	TypeOutput out;
	
	std::atomic<int64_t> num_samples_send {0};
	std::atomic<int64_t> num_samples_recv {0};
	std::atomic<int64_t> num_requests_send {0};
	std::atomic<int64_t> num_requests_recv {0};
	
	// all below shared via mutex
	std::mutex mutex;
	int socket = -1;
	std::map<Hash64, std::map<uint64_t, std::shared_ptr<const Request>>> request_map;
	
	// all below belong to read_loop()
	std::map<Hash64, std::shared_ptr<Pipe>> return_map;		// to keep track of return pipes
	std::set<std::pair<Hash64, Hash64>> incoming;			// map of incoming connections
	
};


} // vnx

#endif /* INCLUDE_VNX_PROXY_H_ */

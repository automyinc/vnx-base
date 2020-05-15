/*
 * AsyncClient.h
 *
 *  Created on: Mar 7, 2020
 *      Author: mad
 */

#ifndef INCLUDE_VNX_ASYNCCLIENT_H_
#define INCLUDE_VNX_ASYNCCLIENT_H_

#include <vnx/Node.h>
#include <vnx/Binary.h>
#include <vnx/exception.h>
#include <vnx/NoSuchService.hxx>
#include <vnx/NoSuchMethod.hxx>
#include <vnx/InternalError.hxx>
#include <vnx/Return.hxx>

#include <functional>


namespace vnx {

class AsyncClient {
public:
	/// Creates a client for the specified service address.
	AsyncClient(Hash64 service_addr);
	
	virtual ~AsyncClient();
	
	/// Returns service address
	Hash64 vnx_get_service_addr() const {
		return vnx_service_addr;
	}
	
	/// Returns this client's src_mac (unique identifier)
	Hash64 vnx_get_src_mac() const {
		return vnx_src_mac;
	}
	
	/// Returns the number of pending requests
	size_t vnx_get_num_pending() const {
		return vnx_num_pending;
	}
	
	/// Sets the node which will receive and process the returns
	void vnx_set_node(Node* node);
	
	/// Called by the receiving node when a return has been received
	void vnx_callback(std::shared_ptr<const Return> result);
	
	/// Called by the receiving node when the remote service has closed
	void vnx_remote_closed();
	
	/** \brief Register a callback function which will be called when a request fails.
	 * 
	 * @param callback Callback function with signature (uint64_t request_id, const std::exception& exception).
	 */
	void vnx_set_error_callback(const std::function<void(uint64_t, const std::exception&)>& callback) {
		vnx_error_callback = callback;
	}
	
	/// Returns list of pending request ids
	virtual std::vector<uint64_t> vnx_get_pending_ids() const = 0;
	
protected:
	size_t vnx_num_pending = 0;
	
	std::function<void(uint64_t, const std::exception&)> vnx_error_callback;
	
	/// Performs the actual request, non-blocking
	uint64_t vnx_request(std::shared_ptr<const Binary> arguments);
	
	virtual void vnx_purge_request(uint64_t request_id) = 0;
	
	virtual void vnx_callback_switch(uint64_t request_id, std::shared_ptr<const Binary> data) = 0;
	
private:
	Node* vnx_node = 0;
	Hash64 vnx_src_mac;
	Hash64 vnx_service_addr;
	uint64_t vnx_next_id = 0;
	
	std::shared_ptr<Pipe> vnx_service_pipe;
	std::shared_ptr<Pipe> vnx_return_pipe;
	
};


} // vnx

#endif /* INCLUDE_VNX_ASYNCCLIENT_H_ */

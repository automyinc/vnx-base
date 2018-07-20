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

#ifndef INCLUDE_VNX_CLIENT_H_
#define INCLUDE_VNX_CLIENT_H_

#include <vnx/Node.h>
#include <vnx/Binary.h>


namespace vnx {

class Client : protected Node {
public:
	Client(Hash64 service_addr);
	
	~Client();
	
protected:
	void vnx_request(std::shared_ptr<const Binary> arguments);
	
protected:
	std::shared_ptr<const Binary> vnx_return_data;
	
	bool vnx_is_async = false;
	
private:
	Hash64 vnx_src_mac;
	Hash64 vnx_service_addr;
	uint64_t vnx_next_id;
	
	std::shared_ptr<Pipe> vnx_service_pipe;
	std::shared_ptr<Pipe> vnx_return_pipe;
	
};


} // vnx

#endif /* INCLUDE_VNX_CLIENT_H_ */

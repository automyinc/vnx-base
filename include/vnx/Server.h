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

#ifndef INCLUDE_VNX_SERVER_H_
#define INCLUDE_VNX_SERVER_H_

#include <vnx/ServerBase.hxx>
#include <vnx/Proxy.h>
#include <vnx/Endpoint.hxx>


namespace vnx {

class Server : public ServerBase {
public:
	Server(const std::string& name_, std::shared_ptr<const Endpoint> endpoint_ = 0);
	
protected:
	void main();
	
	void setup();
	
private:
	void accept_loop();
	
private:
	int server = -1;
	std::shared_ptr<const Endpoint> endpoint;
	Timer* setup_timer = 0;
	
	std::thread thread;
	
};


} // vnx

#endif /* INCLUDE_VNX_SERVER_H_ */

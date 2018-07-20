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

#ifndef VNX_SPYTOOL_H_
#define VNX_SPYTOOL_H_

#include <vnx/SpyToolBase.hxx>
#include <vnx/ProcessClient.hxx>
#include <vnx/ProxyClient.hxx>

#include <set>


namespace vnx {

class SpyTool : public SpyToolBase {
public:
	SpyTool(const std::string& vnx_name_ = "SpyTool");
	
protected:
	void main();
	
	void handle(std::shared_ptr<const Sample> sample);
	
	void update();
	
private:
	std::shared_ptr<ProcessClient> process;
	std::shared_ptr<ProxyClient> proxy;
	
	std::set<std::string> topic_set;
	
};


} // vnx

#endif /* VNX_SPYTOOL_H_ */

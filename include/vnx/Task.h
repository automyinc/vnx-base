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

#ifndef INCLUDE_VNX_TASK_H_
#define INCLUDE_VNX_TASK_H_

#include <vnx/Message.hxx>

#include <functional>


namespace vnx {

class Task : public Message {
public:
	std::function<void()> function;
	
	static std::shared_ptr<Task> create() {
		return std::make_shared<Task>();
	}
	
};


} // vnx

#endif /* INCLUDE_VNX_TASK_H_ */

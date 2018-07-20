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

#ifndef INCLUDE_VNX_TOPICPTR_H_
#define INCLUDE_VNX_TOPICPTR_H_

#include <vnx/Topic.h>


namespace vnx {

class TopicPtr : public std::shared_ptr<Topic> {
public:
	TopicPtr();
	
	explicit TopicPtr(const char* name_);
	
	explicit TopicPtr(const std::string& name_);
	
	TopicPtr(const std::shared_ptr<Topic>& topic_);
	
	TopicPtr& operator=(const char* name_);
	
	TopicPtr& operator=(const std::string& name_);
	
	TopicPtr& operator=(const std::shared_ptr<Topic>& topic_);
	
	operator bool() const;
	
};


} // vnx

#endif /* INCLUDE_VNX_TOPICPTR_H_ */

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

#ifndef INCLUDE_VNX_SUBSCRIBER_H_
#define INCLUDE_VNX_SUBSCRIBER_H_

#include <vnx/Node.h>
#include <vnx/Topic.h>


namespace vnx {

/*
 * A Subscriber is a Node that wants to receive samples.
 * 
 * Repeated calls to subscribe() are counted and
 * an equal number of calls to unsubscribe() are needed to actually unsubscribe.
 * A preemtive call to unsubscribe() can be used to cancel out a later subscribe().
 * 
 * The Subscriber keeps track of subscriptions. It automatically unsubscribes all topics upon exit. 
 */
class Subscriber : public Node {
private:
	struct subscription_t {
		int count = 0;
		std::shared_ptr<Pipe> pipe;
		std::shared_ptr<Topic> topic;
	};
	
public:
	Subscriber();
	
	~Subscriber();
	
	void subscribe(const std::string& domain, const std::string& topic, int max_queue_ms = 100);
	
	void subscribe(const std::string& full_topic_name, int max_queue_ms = 100);
	
	void subscribe(std::shared_ptr<Topic> topic, int max_queue_ms = 100);
	
	void unsubscribe(const std::string& domain, const std::string& topic);
	
	void unsubscribe(const std::string& full_topic_name);
	
	void unsubscribe(std::shared_ptr<Topic> topic);
	
	void unsubscribe_all();
	
	void close();
	
private:
	std::map<Hash64, subscription_t> topic_map;
	
};


} // vnx

#endif /* INCLUDE_VNX_SUBSCRIBER_H_ */

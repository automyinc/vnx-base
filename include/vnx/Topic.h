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

#ifndef INCLUDE_VNX_TOPIC_H_
#define INCLUDE_VNX_TOPIC_H_

#include <vnx/Util.h>
#include <vnx/Node.h>
#include <vnx/Pipe.h>
#include <vnx/TopicInfo.hxx>

#include <unordered_map>


namespace vnx {

class Topic;

/*
 * Get topic known by "topic_name". Creates a new topic if it does not exist already.
 */
std::shared_ptr<Topic> get_topic(const std::string& topic_name);

/*
 * Get topic known by "<domain>.<topic>". Creates a new topic if it does not exist already.
 */
std::shared_ptr<Topic> get_topic(const std::string& domain, const std::string& topic);

/*
 * Get a list of all topics. Does not include domains (ie. only topics which have no children).
 */
std::vector<std::shared_ptr<Topic>> get_all_topics();

/*
 * Get a list of all topics in domain "domain". Does not include sub-domains (ie. only topics which have no children).
 */
std::vector<std::shared_ptr<Topic>> get_all_topics(std::shared_ptr<Topic> domain);


/*
 * A Topic is used to distribute (ie. publish) samples to a number of subscribers.
 */
class Topic {
public:
	Topic(const std::string& topic_name_);
	
	~Topic();
	
	Topic(const Topic& other) = delete;
	Topic& operator=(const Topic& other) = delete;
	
	/*
	 * Get the domain name of this topic.
	 * Exampe: returns "mydomain" for topic "mydomain.mytopic".
	 */
	std::string get_domain_name() const;
	
	/*
	 * The the name of this topic.
	 */
	std::string get_name() const;
	
	/*
	 * Get the CRC64 hash of this topic.
	 */
	Hash64 get_hash() const;
	
	/*
	 * The the topic info for this topic.
	 */
	TopicInfo get_info();
	
	/*
	 * Get a pointer to the parent of this topic (ie. its domain).
	 */
	std::shared_ptr<Topic> get_parent();
	
	/*
	 * Get a list of all direct child topics.
	 */
	std::vector<std::shared_ptr<Topic>> get_children();
	
	/*
	 * Add a subscriber to this topic.
	 */
	void subscribe(std::shared_ptr<Pipe> pipe);
	
	/*
	 * Remove a subscriber from this topic.
	 */
	void unsubscribe(std::shared_ptr<Pipe> pipe);
	
	/*
	 * Publish a sample on this topic.
	 */
	void publish(std::shared_ptr<Sample> sample);
	
	/*
	 * Add a child to this topic. Used internally only.
	 */
	void add_child(std::shared_ptr<Topic> child);
	
	/*
	 * Remove a child from this topic. Used internally only.
	 */
	void remove_child(Topic* child);
	
	/*
	 * Close this topic and all its children.
	 */
	void close();
	
private:
	/*
	 * Forwards the sample to all subscribers.
	 */
	void forward(std::shared_ptr<const Sample> sample);
	
private:
	std::mutex mutex;
	std::condition_variable condition;
	
	std::string domain_name;
	std::string topic_name;
	Hash64 topic_hash;
	
	bool is_closed = false;
	std::shared_ptr<Topic> parent;
	std::unordered_map<Hash64, std::shared_ptr<Topic>> children;
	
	std::list<std::shared_ptr<Pipe>> output;
	
	TopicInfo info;
	
};


} // vnx

#endif /* INCLUDE_VNX_TOPIC_H_ */

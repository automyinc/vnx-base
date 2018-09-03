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

#ifndef INCLUDE_VNX_PUBLISHER_H_
#define INCLUDE_VNX_PUBLISHER_H_

#include <vnx/Topic.h>
#include <vnx/TopicPtr.h>
#include <vnx/Time.h>
#include <vnx/Util.h>
#include <vnx/Sample.hxx>

#include <sstream>


namespace vnx {

/*
 * A Publisher is used to publish samples.
 * 
 * Each publisher has its own unique and randomly created "src_mac".
 * Together with the sequence number a sample can be uniquely identified.
 * 
 * The Publisher automatically attaches a sequence number to each sample published.
 * It keeps a map of current sequence numbers, one for each topic.
 */
class Publisher {
public:
	Publisher();
	
	Publisher(const Publisher& other) = delete;
	Publisher& operator=(const Publisher& other) = delete;
	
	/*
	 * Publish a copy of the value.
	 */
	void publish(const Value& value, TopicPtr topic, uint16_t flags = 0);
	
	/*
	 * Publish the actual value directly. (zero-copy)
	 * WARNING: "value" cannot be modified after this! Otherwise segfaults will be yours!
	 */
	template<typename T>
	void publish(std::shared_ptr<T> value, TopicPtr topic, uint16_t flags = 0) {
		publish(std::shared_ptr<const Value>(value), topic, flags);
	}
	
	/*
	 * Same as above.
	 */
	void publish(std::shared_ptr<const Value> value, TopicPtr topic, uint16_t flags = 0);
	
private:
	const Hash64 src_mac;
	std::unordered_map<Hash64, uint64_t> seq_map;
	
};


/*
 * Used internally by log() functions.
 * Will publish a LogMsg upon destruction of the object.
 */
class LogPublisher {
public:
	LogPublisher(std::shared_ptr<Publisher> publisher, std::ostringstream& stream, const std::string& module, int level, int display_level);
	
	~LogPublisher();
	
	std::ostringstream& out;
	
private:
	std::shared_ptr<Publisher> publisher;
	std::string module;
	int level;
	int display_level;
	
};

LogPublisher log_error();
LogPublisher log_warn();
LogPublisher log_info();
LogPublisher log_debug();


} // vnx

#endif /* INCLUDE_VNX_PUBLISHER_H_ */

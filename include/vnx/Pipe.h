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

#ifndef INCLUDE_VNX_PIPE_H_
#define INCLUDE_VNX_PIPE_H_

#include <vnx/Time.h>
#include <vnx/Message.hxx>

#include <queue>
#include <mutex>
#include <condition_variable>


namespace vnx {

class Node;
class Pipe;

/*
 * Open a new pipe known as "service_name" to Node "node".
 */
std::shared_ptr<Pipe> open_pipe(const std::string& service_name, Node* node, int max_queue_ms = 100);

/*
 * Open a new pipe known by "mac_addr" to Node "node".
 */
std::shared_ptr<Pipe> open_pipe(Hash64 mac_addr, Node* node, int max_queue_ms = 100);

/*
 * Get a pipe to a service called "service_name".
 * Returns 0 if service does not exist.
 */
std::shared_ptr<Pipe> get_pipe(const std::string& service_name);

/*
 * Get a pipe to a node known by "mac_addr".
 * Returns 0 if node does not exist.
 */
std::shared_ptr<Pipe> get_pipe(Hash64 mac_addr);

/*
 * Send a message to service "service_name".
 * Will drop the message if service does not exist.
 */
bool send_msg(const std::string& service_name, std::shared_ptr<const Message> msg);

/*
 * Send a message to a node known by "mac_addr".
 * Will drop the message if node does not exist.
 */
bool send_msg(Hash64 mac_addr, std::shared_ptr<const Message> msg);

/*
 * Unregister a service known by "service_name".
 */
void remove_pipe(const std::string& service_name);

/*
 * Unregister a node known by "mac_addr".
 */
void remove_pipe(Hash64 mac_addr);

/*
 * Close the pipe going to service "service_name".
 */
void close_pipe(const std::string& service_name);

/*
 * Close the pipe going to node known by "mac_addr".
 */
void close_pipe(Hash64 mac_addr);

/*
 * Trigger all nodes listening to any public pipe to exit.
 * Used by the shutdown procedure.
 */
void shutdown_pipes();


/*
 * vnx::Pipe is a basic means of delivering messages to a vnx::Node.
 * The Pipe is one-directional and maintains a queue of messages internally.
 * The maximum queue size is specified in terms of maximum latency in milli-seconds.
 * A maximum queue length of 0 means unlimited.
 * 
 * The Pipe is used to handle any situation without segfaulting.
 * For example: - Sending a message to a Node that does not exist anymore.
 * 				- Returning error messages to Clients for Requests that got left over in the queue.
 */
class Pipe {
public:
	/*
	 * Create a private no-name pipe.
	 */
	Pipe();
	
	/*
	 * Create a public pipe which is known inside this process by "mac_addr".
	 * Used for services and tunnels to receive requests and messages.
	 */
	Pipe(Hash64 mac_addr);
	
	~Pipe();
	
	Pipe(const Pipe& other) = delete;
	Pipe& operator=(const Pipe& other) = delete;
	
	/*
	 * Connect a Pipe to a Node.
	 */
	friend void connect(std::shared_ptr<Pipe> pipe, Node* node, int max_queue_ms = 100);
	
	/*
	 * Send a message through a Pipe.
	 */
	friend bool send_msg(std::shared_ptr<Pipe> pipe, std::shared_ptr<const Message> msg);
	
	/*
	 * Get the next available message. Returns 0 if no message available.
	 */
	std::shared_ptr<const Message> pop();
	
	/*
	 * Temporarily prevent new messages from being pushed into the pipe.
	 */
	void pause();
	
	/*
	 * Resume normal operation after pause() was called.
	 */
	void resume();
	
	/*
	 * Close this pipe.
	 */
	void close();
	
	/*
	 * Get a pointer to the node which is connected to this pipe.
	 * Use only for identification purposes. The node could be deleted at any point in time!
	 */
	Node* get_node();
	
	bool get_is_paused() const { return is_paused; }
	
private:
	/*
	 * Queue entry type that combines the message and timestamp when it was put into the queue.
	 */
	struct entry_t {
		std::shared_ptr<const Message> msg;
		int64_t time = 0;
		entry_t() {}
		explicit entry_t(const std::shared_ptr<const Message>& msg) : msg(msg), time(get_wall_time_micros()) {}
	};
	
	void connect(std::shared_ptr<Pipe> self, Node* node, int max_queue_ms = 100);
	
	/*
	 * Push a new message onto the queue. Used exclusively by send_msg().
	 */
	bool push(std::shared_ptr<Pipe> self, std::shared_ptr<const Message> msg);
	
private:
	std::mutex mutex;
	std::condition_variable condition;
	
	Node* node = 0;
	Hash64 mac_addr;
	
	int64_t max_queue_us = 100000;
	
	std::queue<entry_t> queue;
	
	bool is_paused = false;
	
	friend class Node;
	
};


} // vnx

#endif /* INCLUDE_VNX_PIPE_H_ */

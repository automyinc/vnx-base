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

#ifndef INCLUDE_VNX_NODE_H_
#define INCLUDE_VNX_NODE_H_

#include <vnx/Pipe.h>

#include <list>


namespace vnx {

/**
 * vnx::Node is a base class for anything that wants to communicate via vnx::Pipe.
 * It gives an interface to read messages from a number of pipes.
 * It also keeps track of and automatically closes all connected pipes on shutdown.
 */
class Node {
public:
	Node() {}
	
	virtual ~Node();
	
	Node(const Node& other) = delete;
	Node& operator=(const Node& other) = delete;
	
	/**
	 * Notify this node that a new message is available on pipe "pipe".
	 * Needs to be thread safe!
	 */
	virtual void notify(std::shared_ptr<Pipe> pipe);
	
	/**
	 * Trigger this node to shut down.
	 * Needs to be thread safe!
	 */
	virtual void exit();
	
protected:
	std::mutex vnx_mutex;
	
	volatile bool vnx_do_run = true;
	
	/**
	 * Read the next message if one is available. Does not wait.
	 * Returns 0 if no message is available.
	 */
	std::shared_ptr<const Message> read();
	
	/**
	 * Read the next message. Waits indefinitely for one to arrive.
	 * Returns 0 if shutdown is triggered.
	 */
	std::shared_ptr<const Message> read_blocking();
	
	/**
	 * Read the next message. Waits timeout_us for one to arrive.
	 * Returns 0 in case of timeout or shutdown is triggered.
	 */
	std::shared_ptr<const Message> read_blocking(int64_t timeout_us);
	
	/**
	 * Close all pipes and clean up.
	 * Can be overridden by derived classes but make sure to call this base version also.
	 */
	virtual void close();
	
private:
	bool add_pipe(std::shared_ptr<Pipe> pipe);		/// attach a new pipe to this node
	
	void remove_pipe(Pipe* pipe);					/// remove a pipe from this node
	
private:
	std::condition_variable condition;
	
	std::queue<std::shared_ptr<Pipe>> notify_queue;		// list of pipes that have messages available
	
	std::list<std::shared_ptr<Pipe>> pipe_list;			// list of pipes that are attached to this node
	
	friend class Pipe;
	
};


} // vnx

#endif /* INCLUDE_VNX_NODE_H_ */

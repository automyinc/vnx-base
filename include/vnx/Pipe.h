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

/// Open a new pipe known as \p service_name to Node \p node.
std::shared_ptr<Pipe> open_pipe(const std::string& service_name, Node* node, int max_queue_ms);

/// Open a new pipe known by \p mac_addr to Node \p node.
std::shared_ptr<Pipe> open_pipe(Hash64 mac_addr, Node* node, int max_queue_ms);

/** \brief Get a pipe to a service called \p service_name.
 * 
 * Returns null if service does not exist.
 */
std::shared_ptr<Pipe> get_pipe(const std::string& service_name);

/** \brief Get a pipe to a node known by \p mac_addr.
 * 
 * Returns 0 if node does not exist.
 */
std::shared_ptr<Pipe> get_pipe(Hash64 mac_addr);

/** \brief Connect \p pipe to \p peer.
 * 
 * Returns false in case of failure.
 */
bool connect(std::shared_ptr<Pipe> pipe, std::shared_ptr<Pipe> peer, uint16_t flags);

/** \brief Disconnect peer from \p pipe.
 * 
 * Returns false in case of failure.
 */
bool disconnect(std::shared_ptr<Pipe> pipe, Hash64 peer_mac);

/** \brief Send a message to service \p service_name.
 * 
 * Will drop the message if service does not exist.
 */
bool send_msg(const std::string& service_name, std::shared_ptr<const Message> msg);

/** \brief Send a message to a node known by \p mac_addr.
 * 
 * Will drop the message if node does not exist.
 */
bool send_msg(Hash64 mac_addr, std::shared_ptr<const Message> msg);

/// Send a message through a pipe.
bool send_msg(std::shared_ptr<Pipe> pipe, std::shared_ptr<const Message> msg);

/** \brief Send a message through a pipe.
 * 
 * Applies given flags before sending: msg->flags |= flags;
 */
bool send_msg(std::shared_ptr<Pipe> pipe, std::shared_ptr<Message> msg, uint16_t flags);

/// Connect a pipe to a node.
void connect(std::shared_ptr<Pipe> pipe, Node* node, int max_queue_ms);

/// Unregister service known by \p service_name.
void remove_pipe(const std::string& service_name);

/// Unregister node known by \p mac_addr.
void remove_pipe(Hash64 mac_addr);

/// Close the pipe going to service \p service_name.
void close_pipe(const std::string& service_name);

/// Close the pipe going to node known by \p mac_addr.
void close_pipe(Hash64 mac_addr);

/** \brief Trigger all nodes listening to any public pipe to exit.
 * 
 * Used by the shutdown procedure.
 */
void shutdown_pipes();


/** \brief Pipe is used to deliver messages to a Node.
 * 
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
	static const int UNLIMITED = 0;		///< Denotes unlimited queue length (max_queue_ms == 0)
	
	/// Create a private no-name pipe.
	Pipe();
	
	/** \brief Create a public pipe which is known inside this process by \p mac_addr.
	 * 
	 * Used for services and tunnels to receive requests and messages.
	 */
	Pipe(Hash64 mac_addr);
	
	~Pipe();
	
	Pipe(const Pipe& other) = delete;
	Pipe& operator=(const Pipe& other) = delete;
	
	static std::shared_ptr<Pipe> create();
	
	/// Connect a Pipe to a Node. (thread-safe)
	friend void connect(std::shared_ptr<Pipe> pipe, Node* node, int max_queue_ms);
	
	/// Connect another Pipe to this Pipe, which will be notified if this pipe is closed. (thread-safe)
	friend bool connect(std::shared_ptr<Pipe> pipe, std::shared_ptr<Pipe> peer, uint16_t flags);
	
	/// Disconnect another Pipe from this Pipe. (thread-safe)
	friend bool disconnect(std::shared_ptr<Pipe> pipe, Hash64 peer_mac);
	
	/// Send a message through a Pipe. (thread-safe)
	friend bool send_msg(std::shared_ptr<Pipe> pipe, std::shared_ptr<const Message> msg);
	
	/** \brief Get the next available message.
	 * 
	 * Returns 0 if no message available. (thread-safe)
	 */
	std::shared_ptr<const Message> pop();
	
	/// Temporarily prevent new messages from being pushed into the pipe. (thread-safe)
	void pause();
	
	/// Resume normal operation after pause() was called. (thread-safe)
	void resume();
	
	/// Close this pipe. (thread-safe)
	void close();
	
	/** \brief Get a pointer to the node which is connected to this pipe.
	 * 
	 * Only for identification purposes, the node could be deleted at any point in time!
	 */
	Node* get_node() const;
	
	/// Returns mac address of this pipe.
	Hash64 get_mac_addr() const {
		return mac_addr;
	}
	
	/// Returns if pipe is currently paused.
	bool is_paused() const;
	
	/// Returns true if this pipe has a mac address.
	bool is_private() const;
	
private:
	/**
	 * Queue entry type that combines the message and timestamp when it was put into the queue.
	 */
	struct entry_t {
		std::shared_ptr<const Message> msg;
		int64_t time = 0;
		entry_t() = default;
		explicit entry_t(std::shared_ptr<const Message> msg) : msg(std::move(msg)), time(get_wall_time_micros()) {}
	};
	
	void connect(std::shared_ptr<Pipe> self, Node* node, int max_queue_ms);
	
	bool connect(std::shared_ptr<Pipe> peer, uint16_t flags);
	
	bool disconnect(Hash64 peer_mac);
	
	/// Push a new message onto the queue. Used exclusively by send_msg().
	bool push(std::shared_ptr<Pipe> self, std::shared_ptr<const Message> msg);
	
private:
	mutable std::mutex mutex;
	mutable std::condition_variable condition;
	
	Node* node = 0;
	Hash64 mac_addr;
	bool is_paused_ = false;
	
	int64_t max_queue_us = 0;
	std::queue<entry_t> queue;
	
	std::map<Hash64, std::shared_ptr<Pipe>> peer_map;
	
	friend class Node;
	
};


} // vnx

#endif /* INCLUDE_VNX_PIPE_H_ */

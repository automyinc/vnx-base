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

#ifndef INCLUDE_VNX_MODULE_H_
#define INCLUDE_VNX_MODULE_H_

#include <vnx/Time.h>
#include <vnx/Hash128.h>
#include <vnx/Publisher.h>
#include <vnx/Subscriber.h>
#include <vnx/AsyncClient.h>
#include <vnx/LogMsg.hxx>

#include <thread>
#include <sstream>


namespace vnx {

/// Unique identifier for a Request (src_mac, request_id)
typedef std::pair<Hash64, uint64_t> request_id_t;

/** \brief Module is the base class for all user Modules.
 * 
 * A Module has it's own thread and main() function, just like a normal process.
 * The user's implementation will inherit from the generated base class which in turn
 * inherits from this class.
 * 
 * The Module class handles timer callbacks, receiving of Sample%s as well as processing
 * of Request%s inside it's main() function. The user can override main() to implement
 * initialization and cleanup functionality, but must call Module::main() at some point.
 */
class Module : protected Subscriber {
public:
	/** \brief Creates a new Module with given name.
	 * 
	 * @param name_ Module name (does not have to be unique)
	 */
	Module(const std::string& name_);
	
	~Module();
	
	static const int UNLIMITED = Pipe::UNLIMITED;		///< Shortcut to denote unlimited queue length
	
	static const int BLOCKING = Message::BLOCKING;		///< Flag to send blocking messages
	
	static const int ERROR = LogMsg::ERROR;
	static const int WARN = LogMsg::WARN;
	static const int INFO = LogMsg::INFO;
	static const int DEBUG = LogMsg::DEBUG;
	
	virtual Hash64 get_type_hash() const = 0;
	virtual const char* get_type_name() const = 0;
	
	virtual void read(std::istream& _in) = 0;
	virtual void write(std::ostream& _out) const = 0;
	
	virtual void accept(vnx::Visitor& _visitor) const = 0;
	
	friend std::ostream& operator<<(std::ostream& _out, const Module& _value);
	friend std::istream& operator>>(std::istream& _in, Module& _value);
	
	Node* get_vnx_node();				///< Returns a pointer to vnx::Node sub-class
	
	std::string get_vnx_name();			///< Returns the module name (Module::vnx_name)
	
	bool vnx_virtual_time = true;		///< If to use virtual time for timers
	
	int vnx_log_level = INFO;			///< The display log level of this module (see LogMsg)
	
	int64_t vnx_heartbeat_interval_ms = 1000;	///< Interval at which to publish ModuleInfo on vnx.module_info [ms]
	
protected:
	const std::string vnx_name;			///< Name of the module
	
	std::shared_ptr<const Sample> vnx_sample;		///< Current Sample being processed (null otherwise)
	
	std::shared_ptr<const Request> vnx_request;		///< Current Request being processed (null otherwise)
	
	std::shared_ptr<const Return> vnx_return;		///< Current Return being processed (null otherwise)
	
	std::map<Hash64, std::shared_ptr<const Endpoint>> vnx_remotes;		///< Map of connected processes (process id => endpoint)
	
	/** \brief Publish a copy of the value.
	 * 
	 * @param flags List of or'ed flags for Message, for example Message::BLOCKING
	 */
	void publish(const Value& value, TopicPtr topic, uint16_t flags = 0) {
		publisher->publish(value.clone(), topic, flags);
	}
	
	/** \brief Publish the actual value directly. (zero-copy)
	 * 
	 * @param flags List of or'ed flags for Message, for example Message::BLOCKING
	 * 
	 * WARNING: \p value may not be modified anymore after this call, since other threads have a pointer now.
	 */
	template<typename T>
	void publish(std::shared_ptr<T> value, TopicPtr topic, uint16_t flags = 0) {
		publisher->publish(value, topic, flags);
	}
	
	/** \brief Publishes log output.
	 * 
	 * Use ERROR, WARN, INFO, DEBUG or custom level.
	 * Usage: log(level).out << "..."; 		// no std::endl needed at the ned
	 */
	LogPublisher log(int level) const;
	
	/// Returns false if this module or the process is being shut down.
	bool vnx_do_run() const;
	
	/** \brief Create a new timer.
	 * 
	 * Can be started manually using Timer::reset().
	 * Can be turned into a repeating timer by setting Timer::is_repeat = true;
	 * Usage: add_timer(std::bind(&Class::function, this));
	 */
	std::shared_ptr<Timer> add_timer(const std::function<void()>& func);
	
	/** \brief Create and start a repeating timer.
	 * 
	 * Can be stopped using Timer::stop(). Can be restarted using Timer::reset().
	 * Usage: set_timer_micros(interval_us, std::bind(&Class::function, this));
	 */
	std::shared_ptr<Timer> set_timer_micros(int64_t interval_us, const std::function<void()>& func);
	
	/** \brief Create and start a repeating timer.
	 * 
	 * Can be stopped using Timer::stop(). Can be restarted using Timer::reset().
	 * Usage: set_timer_millis(interval_ms, std::bind(&Class::function, this));
	 */
	std::shared_ptr<Timer> set_timer_millis(int64_t interval_ms, const std::function<void()>& func);
	
	/** \brief Adds an AsyncClient to this module.
	 * 
	 * Needs to be done before calling any service functions.
	 */
	void add_async_client(std::shared_ptr<AsyncClient> client);
	
	/** \brief Removes an AsyncClient from this module.
	 * 
	 * Any pending requests/returns will be discarded.
	 */
	void rem_async_client(std::shared_ptr<AsyncClient> client);
	
	/** \brief Called before main() from the thread starting the module.
	 * 
	 * Used to make sure that the module is initialized after Handle::start() returns.
	 * For example, open_pipe() calls should be done in init() such that a client connecting after
	 * Handle::start() is guaranteed to succeed, which would not be the case if open_pipe() was called in
	 * main() since that is a different thread that was just spawned in the background and it is undefined when
	 * it will actually start to execute.
	 */
	virtual void init() {}
	
	/** \brief Main function, just like the real int main().
	 * 
	 * Called from within a new thread that is spawned when starting the Module.
	 * Make sure to call Super::main() (ie. Module::main()) at some point when over-riding it,
	 * since all the processing is done in Module::main().
	 */
	virtual void main();
	
	/// %Process a Message (internal use and special cases only)
	virtual void handle(std::shared_ptr<const Message> msg);
	
	/// %Process a Sample (internal use and special cases only)
	virtual void handle(std::shared_ptr<const Sample> sample);
	
	/// %Process a Request (internal use and special cases only)
	virtual std::shared_ptr<const Return> handle(std::shared_ptr<const Request> request);
	
	/// %Process a Return (internal use and special cases only)
	virtual bool handle(std::shared_ptr<const Return> result);
	
	/// Call handle() function for a Sample (internal use and special cases only)
	virtual void vnx_handle_switch(std::shared_ptr<const Sample> sample) = 0;
	
	/// Call service function for a Request (internal use and special cases only)
	virtual std::shared_ptr<Value> vnx_call_switch(TypeInput& in, const TypeCode* call_type, const vnx::request_id_t& request_id) = 0;
	
	/// Sends a Return back to the client [thread-safe]
	virtual bool vnx_async_return(const vnx::request_id_t& request_id, std::shared_ptr<Value> return_value) const;
	
private:
	void heartbeat();
	
	void entry();
	
	void start();
	
	bool is_running();
	
	void wait();
	
	void detach(std::shared_ptr<Module> self_ptr_);
	
private:
	Hash64 module_id;
	TimeControl time_state;
	std::shared_ptr<Publisher> publisher;
	mutable std::ostringstream log_stream;
	std::unordered_map<Hash128, uint64_t> seq_map;
	std::vector<std::shared_ptr<Timer>> timers;
	
	mutable std::mutex async_mutex;
	std::map<Hash64, std::shared_ptr<AsyncClient>> async_clients;
	mutable std::map<request_id_t, std::shared_ptr<Return>> async_requests;
	
	std::thread thread;
	std::shared_ptr<Module> self_ptr;
	
	template<typename T>
	friend class Handle;
	
};


/** \brief Smart pointer class for Modules.
 * 
 * Handle is wrapper around std::shared_ptr<T> for Modules.
 * It will automatically stop and delete a Module unless it has been detached.
 */
template<typename T>
class Handle {
public:
	Handle() {}
	
	Handle(T* module_) {
		*this = module_;
	}
	
	Handle& operator=(T* module_) {
		module = std::shared_ptr<T>(module_, [](T* m) {
			if(m) {
				m->exit();
				m->wait();
				delete m;
			}
        });
		return *this;
	}
	
	operator bool() {
		return bool(module);
	}
	
	/**
	 * Access the module. Makes sure it is not already running.
	 */
	T& operator*() {
		if(module->is_running()) {
			throw std::logic_error("Handle: module already running");
		}
		return *module;
	}
	
	/**
	 * Access the module. Makes sure it is not already running.
	 */
	T* operator->() {
		if(module->is_running()) {
			throw std::logic_error("Handle: module already running");
		}
		return module.get();
	}
	
	/**
	 * Starts the module in a new thread. Returns after Module::init() is done.
	 */
	void start() {
		if(module) {
			module->start();
		}
	}
	
	/**
	 * Starts the module and detaches the handle. Module will self destruct upon exit.
	 */
	void start_detached() {
		start();
		detach();
	}
	
	/**
	 * Detaches the module. Module will self destruct upon exit.
	 */
	void detach() {
		if(module) {
			module->detach(module);
			module = 0;
		}
	}
	
	/**
	 * Wait for the module to exit.
	 */
	void wait() {
		if(module) {
			module->wait();
			module = 0;
		}
	}
	
	/**
	 * Trigger the module to exit.
	 */
	void exit() {
		if(module) {
			module->exit();
		}
	}
	
	/**
	 * Trigger the module to exit and wait for it to finish.
	 */
	void close() {
		if(module) {
			module->exit();
			module->wait();
			module = 0;
		}
	}
	
private:
	std::shared_ptr<T> module;
	
};


inline bool operator<(const request_id_t& lhs, const request_id_t& rhs) {
	if(lhs.first == rhs.first) {
		return lhs.second < rhs.second;
	}
	return lhs.first < rhs.first;
}

inline bool operator==(const request_id_t& lhs, const request_id_t& rhs) {
	return lhs.first == rhs.first && lhs.second == rhs.second;
}


} // vnx

namespace std {
	template<> struct hash<vnx::request_id_t> {
		size_t operator()(const vnx::request_id_t& x) const {
			return x.first ^ x.second;
		}
	};
} // std

#endif /* INCLUDE_VNX_MODULE_H_ */

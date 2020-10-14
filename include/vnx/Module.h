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
#include <vnx/Task.h>
#include <vnx/Hash128.h>
#include <vnx/Publisher.h>
#include <vnx/Subscriber.h>
#include <vnx/AsyncClient.h>
#include <vnx/request_id_t.h>
#include <vnx/LogMsg.hxx>
#include <vnx/FlowMessage.hxx>

#include <thread>
#include <sstream>
#include <functional>


namespace vnx {

template<typename T>
class Handle;

/// Adds a module to the global registry (used by vnx::Handle only)
void add_module(std::shared_ptr<Module> module);

/// Removes a module from the global registry (used by vnx::Handle only)
void remove_module(std::shared_ptr<Module> module);

/// Returns the latest module handle found for given name.
Handle<Module> get_module(const std::string& name);

/// Returns all module handles found for the given name.
std::vector<Handle<Module>> get_modules(const std::string& name);

/// Returns array of all modules.
std::vector<std::pair<std::string, Handle<Module>>> get_all_modules();


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
	virtual const TypeCode* get_type_code() const = 0;
	
	virtual void read(std::istream& _in) = 0;
	virtual void write(std::ostream& _out) const = 0;
	virtual void accept(vnx::Visitor& _visitor) const = 0;
	
	virtual Object to_object() const = 0;
	virtual void from_object(const Object& _object) = 0;

	virtual Variant get_field(const std::string& _name) const = 0;
	virtual void set_field(const std::string& _name, const Variant& _value) = 0;

	friend std::ostream& operator<<(std::ostream& _out, const Module& _value);
	friend std::istream& operator>>(std::istream& _in, Module& _value);
	
	Node* vnx_get_node();				///< Returns a pointer to vnx::Node sub-class
	
	std::string vnx_get_name();			///< Returns the module name (Module::vnx_name)
	
	Object vnx_get_config_object() const;		///< Returns entire config

	Variant vnx_get_config(const std::string& name);		///< Returns current config value

	void vnx_set_config_object(const Object& config);		///< Sets multiple config values

	void vnx_set_config(const std::string& name, const Variant& value);		///< Sets a new config value

	TypeCode vnx_get_type_code() const;	///< Returns the module's type code

	bool vnx_virtual_time = true;		///< If to use virtual time for timers
	
	bool vnx_clean_exit = false;		///< If to process all remaining messages on shutdown

	bool vnx_auto_decompress = true;	///< If to automatically decompress Sample values

	int vnx_log_level = INFO;			///< The display log level of this module (see LogMsg)
	
	int64_t vnx_time_slice_us = 10000;			///< Maximum time to spend processing messages in a loop [us]
	
	int64_t vnx_heartbeat_interval_ms = 1000;	///< Interval at which to publish ModuleInfo on vnx.module_info [ms]
	
protected:
	const std::string vnx_name;			///< Name of the module
	
	std::shared_ptr<const Sample> vnx_sample;		///< Current Sample being processed (null otherwise)
	
	std::shared_ptr<const Request> vnx_request;		///< Current Request being processed (null otherwise)
	
	std::shared_ptr<const Return> vnx_return;		///< Current Return being processed (null otherwise)
	
	std::shared_ptr<const Task> vnx_task;			///< Current Task being processed (null otherwise)
	
	std::map<Hash64, std::shared_ptr<const Endpoint>> vnx_remotes;		///< Map of connected processes (process id => endpoint)
	
	/** \brief Publish a copy of the value. [thread-safe]
	 * 
	 * @param flags List of or'ed flags for Message, for example Message::BLOCKING
	 */
	void publish(const Value& value, TopicPtr topic, uint16_t flags = 0) const {
		publisher->publish(value.clone(), topic, flags);
	}
	
	/** \brief Publish the actual value directly. (zero-copy) [thread-safe]
	 * 
	 * @param flags List of or'ed flags for Message, for example Message::BLOCKING
	 * 
	 * WARNING: \p value may not be modified anymore after this call, since other threads have a pointer now.
	 */
	template<typename T>
	void publish(std::shared_ptr<T> value, TopicPtr topic, uint16_t flags = 0) const {
		publisher->publish(value, topic, flags);
	}
	
	/** \brief Adds a task to this modules message queue. [thread-safe]
	 * 
	 * The task will be processed in the main() loop like an incoming message.
	 * Returns false in case of shutdown.
	 */
	bool add_task(const std::function<void()>& func) const;
	
	/** \brief Publishes log output. [thread-safe]
	 * 
	 * Use ERROR, WARN, INFO, DEBUG or custom level.
	 * Usage: log(level) << "..."; 		// no std::endl needed at the end
	 */
	LogPublisher log(int level) const {
		return LogPublisher(publisher, vnx_name, level, vnx_log_level);
	}
	
	/// Returns false if this module or the process is being shut down. [thread-safe]
	bool vnx_do_run() const;
	
	/// Restarts the Module in-place, calling init() and main() again after clearing state.
	void vnx_restart();

	/// Stops and deletes the Module, same as Handle::close()
	void vnx_close();

	/** \brief Create a new timer.
	 * 
	 * The created timer is not started/activated by this call.
	 * Can be started manually using Timer::reset() or Timer::set_millis() / Timer::set_micros().
	 * Can be turned into a repeating timer by setting Timer::is_repeat = true;
	 * Usage: add_timer(std::bind(&Class::function, this));
	 */
	std::shared_ptr<Timer> add_timer(const std::function<void()>& func);
	
	/** \brief Creates a temporary timer, for one time use.
	 *
	 * The created timer is already started/activated.
	 * Can be stopped using Timer::stop().
	 * Can be restarted using Timer::reset() or Timer::set_millis() / Timer::set_micros().
	 * Usage: set_timeout_micros(interval_us, std::bind(&Class::function, this));
	 */
	std::weak_ptr<Timer> set_timeout_micros(int64_t interval_us, const std::function<void()>& func);

	/** \brief Creates a temporary timer, for one time use.
	 *
	 * The created timer is already started/activated.
	 * Can be stopped using Timer::stop().
	 * Can be restarted using Timer::reset() or Timer::set_millis() / Timer::set_micros().
	 * Usage: set_timeout_millis(interval_us, std::bind(&Class::function, this));
	 */
	std::weak_ptr<Timer> set_timeout_millis(int64_t interval_ms, const std::function<void()>& func);

	/** \brief Create and start a repeating timer.
	 * 
	 * The created timer is already started/activated.
	 * Can be stopped using Timer::stop().
	 * Can be restarted using Timer::reset() or Timer::set_millis() / Timer::set_micros().
	 * Usage: set_timer_micros(interval_us, std::bind(&Class::function, this));
	 */
	std::shared_ptr<Timer> set_timer_micros(int64_t interval_us, const std::function<void()>& func);
	
	/** \brief Create and start a repeating timer.
	 * 
	 * The created timer is already started/activated.
	 * Can be stopped using Timer::stop().
	 * Can be restarted using Timer::reset() or Timer::set_millis() / Timer::set_micros().
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
	
	/// %Process a Task (internal use and special cases only)
	virtual void handle(std::shared_ptr<const Task> task);
	
	/// %Process a FlowMessage (internal use and special cases only)
	virtual void handle(std::shared_ptr<const FlowMessage> msg);
	
	/// %Process a Request (internal use and special cases only)
	virtual std::shared_ptr<const Return> handle(std::shared_ptr<const Request> request);
	
	/// %Process a Return (internal use and special cases only)
	virtual bool handle(std::shared_ptr<const Return> result);
	
	/// Call handle() function for a Sample (internal use and special cases only)
	virtual void vnx_handle_switch(std::shared_ptr<const Sample> sample) = 0;
	
	/// Call service function for a Request (internal use and special cases only)
	virtual std::shared_ptr<Value> vnx_call_switch(std::shared_ptr<const Value> method, const vnx::request_id_t& request_id) = 0;
	
	/// Sends a Return back to the client [thread-safe]
	virtual bool vnx_async_return(const vnx::request_id_t& request_id, std::shared_ptr<const Value> return_value) const;
	
private:
	void heartbeat();
	
	void setup();

	void entry();
	
	void start();
	
	bool is_running();
	
	void wait();
	
	void detach(std::shared_ptr<Module> self_ptr_);
	
	std::shared_ptr<Module> attach();

private:
	Hash64 module_id;
	TimeControl time_state;
	std::shared_ptr<Publisher> publisher;
	std::unordered_map<Hash128, uint64_t> seq_map;
	std::set<std::shared_ptr<Timer>> timers;
	std::shared_ptr<Pipe> task_pipe;
	std::map<std::string, std::string> type_map;
	
	mutable std::mutex async_mutex;
	std::map<Hash64, std::shared_ptr<AsyncClient>> async_clients;
	mutable std::map<request_id_t, std::shared_ptr<Return>> async_requests;
	
	std::thread thread;
	std::shared_ptr<Module> self_ptr;
	bool do_restart = false;
	
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
	
	/// Takes ownership of the Module.
	Handle(T* module_) {
		*this = module_;
	}
	
	/// Internal use only.
	Handle(const std::shared_ptr<T>& module_) {
		*this = module_;
	}

	template<typename S>
	Handle(const Handle<S>& other) {
		*this = other;
	}

	/// Will close the Module if it's not detached and this is the only Handle.
	~Handle() {
		if(module && module.use_count() == 1) {
			close();
		}
	}

	Handle& operator=(T* module_) {
		close();
		module = std::shared_ptr<T>(module_);
		return *this;
	}

	Handle& operator=(const std::shared_ptr<T>& module_) {
		close();
		module = module_;
		return *this;
	}

	template<typename S>
	Handle& operator=(const Handle<S>& other) {
		close();
		module = other.shared_ptr();
		return *this;
	}

	operator bool() {
		return bool(module);
	}
	
	/// Access the module. Makes sure it is not already running.
	T& operator*() {
		if(module->is_running()) {
			throw std::logic_error("Handle: module already running");
		}
		return *module;
	}
	
	/// Access the module. Makes sure it is not already running.
	T* operator->() {
		if(module->is_running()) {
			throw std::logic_error("Handle: module already running");
		}
		return module.get();
	}
	
	/** \brief Starts the module in a new thread.
	 *
	 * Returns after Module::init() is done.
	 */
	void start() {
		if(module) {
			add_module(module);
			try {
				module->start();
			} catch(...) {
				remove_module(module);
				throw;
			}
		}
	}
	
	/** \brief Starts the module and detaches it.
	 *
	 * Module will self destruct upon exit.
	 */
	void start_detached() {
		start();
		detach();
	}
	
	/** \brief Detaches the module.
	 *
	 * Module will self destruct upon exit.
	 */
	void detach() {
		if(module) {
			module->detach(module);
		}
	}
	
	/** \brief Attach to a detached module.
	 *
	 * @return If attach was successful, ie. the Module was detached and still running.
	 */
	bool attach() {
		if(module) {
			return bool(module->attach());
		}
		return false;
	}

	/// Wait for the module to exit / finish.
	void wait() {
		if(module) {
			module->wait();
			remove_module(module);
			module = nullptr;
		}
	}
	
	/// Trigger the module to exit.
	void exit() {
		if(module) {
			module->exit();
		}
	}
	
	/// Trigger the module to exit and wait for it to finish.
	void close() {
		exit();
		wait();
	}

	/// Internal use only.
	std::shared_ptr<T> shared_ptr() const {
		return module;
	}

private:
	std::shared_ptr<T> module;
	
};


} // vnx

#endif /* INCLUDE_VNX_MODULE_H_ */

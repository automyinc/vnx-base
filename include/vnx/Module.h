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
#include <vnx/Publisher.h>
#include <vnx/Subscriber.h>
#include <vnx/LogMsg.hxx>

#include <thread>
#include <sstream>


namespace vnx {

class Module : protected Subscriber {
public:
	Module(const std::string& name_);
	
	~Module();
	
	static const int BLOCKING = Message::BLOCKING;
	
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
	
	int vnx_log_level;				// the log level of this module
	
protected:
	std::string vnx_name;			// name of the module
	
	/*
	 * Publish a copy of the value.
	 */
	void publish(const Value& value, TopicPtr topic, uint16_t flags = 0) {
		publisher->publish(value.clone(), topic, flags);
	}
	
	/*
	 * Publish the actual value directly. (zero-copy)
	 * WARNING: "value" cannot be modified after this! Otherwise segfaults will be yours!
	 */
	template<typename T>
	void publish(std::shared_ptr<T> value, TopicPtr topic, uint16_t flags = 0) {
		publisher->publish(value, topic, flags);
	}
	
	/*
	 * Publishes log output. Use ERROR, WARN, INFO, DEBUG or custom level.
	 * Usage: log(?).out << "..."; 		// no std::endl needed at the ned
	 */
	LogPublisher log(int level);
	
	/*
	 * Create a new timer.
	 * Can be started manually using Timer::reset().
	 * Can be turned into a repeating timer by setting Timer::is_repeat = true;
	 * Usage: add_timer(std::bind(?, this));
	 */
	Timer* add_timer(const std::function<void()>& func);
	
	/*
	 * Create and start a repeating timer.
	 * Can be stopped using Timer::stop().
	 * Can be restarted using Timer::reset().
	 * Usage: set_timer_?(?, std::bind(?, this));
	 */
	Timer* set_timer_micros(int64_t interval_us, const std::function<void()>& func);
	Timer* set_timer_millis(int64_t interval_ms, const std::function<void()>& func);
	
	/*
	 * Called before main() from the thread starting the module.
	 * Used to make sure that the module is initialized after Handle::start() returns.
	 */
	virtual void init() {}
	
	/*
	 * Main function, just like the real int main().
	 * Make sure to call Super::main() at some point when over-riding it.
	 */
	virtual void main();
	
	/*
	 * Shuts down the module. (thread safe)
	 */
	void exit();
	
	/*
	 * These are internal functions that can be overridden in special cases.
	 */
	virtual void handle(std::shared_ptr<const Message> msg);
	virtual void handle(std::shared_ptr<const Sample> sample);
	virtual void handle_switch(std::shared_ptr<const Sample> sample) = 0;
	
	virtual std::shared_ptr<const Return> handle(std::shared_ptr<const Request> value);
	virtual bool call_switch(TypeInput& in, TypeOutput& out, const TypeCode* call_type, const TypeCode* return_type) = 0;
	
private:
	void entry();
	
	void start();
	
	bool is_running();
	
	void wait();
	
	void detach(std::shared_ptr<Module> self_ptr_);
	
private:
	std::shared_ptr<Publisher> publisher;
	TimeControl time_state;
	std::ostringstream log_stream;
	std::unordered_map<uint64_t, uint64_t> seq_map;
	std::vector<std::shared_ptr<Timer>> timers;
	
	std::thread thread;
	std::shared_ptr<Module> self_ptr;
	
	template<typename T>
	friend class Handle;
	
};


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
	
	/*
	 * Access the module. Makes sure it is not already running.
	 */
	T& operator*() {
		if(module->is_running()) {
			throw std::logic_error("Handle: module already running");
		}
		return *module;
	}
	
	/*
	 * Access the module. Makes sure it is not already running.
	 */
	T* operator->() {
		if(module->is_running()) {
			throw std::logic_error("Handle: module already running");
		}
		return module.get();
	}
	
	/*
	 * Starts the module in a new thread. Returns after Module::init() is done.
	 */
	void start() {
		if(module) {
			module->start();
		}
	}
	
	/*
	 * Starts the module and detaches the handle. Module will self destruct upon exit.
	 */
	void start_detached() {
		start();
		detach();
	}
	
	/*
	 * Detaches the module. Module will self destruct upon exit.
	 */
	void detach() {
		if(module) {
			module->detach(module);
			module = 0;
		}
	}
	
	/*
	 * Wait for the module to exit.
	 */
	void wait() {
		if(module) {
			module->wait();
			module = 0;
		}
	}
	
	/*
	 * Trigger the module to exit.
	 */
	void exit() {
		if(module) {
			module->exit();
		}
	}
	
	/*
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


} // vnx

#endif /* INCLUDE_VNX_MODULE_H_ */

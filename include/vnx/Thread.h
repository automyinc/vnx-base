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

#ifndef INCLUDE_VNX_THREAD_H
#define INCLUDE_VNX_THREAD_H

#include <vnx/Subscriber.h>
#include <vnx/Publisher.h>

#include <thread>


namespace vnx {

/*
 * Thread is a base class for worker threads that live inside
 * a normal module.
 */
class Thread : protected Subscriber, protected Publisher {
public:
	Thread(const std::string& vnx_name_) : vnx_name(vnx_name_) {}
	
	~Thread() {
		stop();
	}
	
	void start() {
		if(!thread.joinable()) {
			init();
			thread = std::thread(&Thread::entry, this);
		}
	}
	
	void join() {
		if(thread.joinable()) {
			thread.join();
		}
	}
	
	void stop() {
		exit();
		notify(nullptr);
		join();
	}
	
protected:
	std::string vnx_name;
	
	/*
	 * Will be called before starting this thread to ensure initialization
	 * is done before starting another thread.
	 */
	virtual void init() {}
	
	/*
	 * Main thread function.
	 */
	virtual void main() = 0;
	
private:
	void entry();
	
private:
	std::thread thread;
	
};


} // vnx

#endif // INCLUDE_VNX_THREAD_H

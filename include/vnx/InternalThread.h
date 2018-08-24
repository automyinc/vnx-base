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

#ifndef INCLUDE_VNX_INTERNALTHREAD_H
#define INCLUDE_VNX_INTERNALTHREAD_H

#include <vnx/Publisher.h>

#include <thread>
#include <mutex>
#include <condition_variable>


namespace vnx {

/*
 * InternalThread is a base class for worker threads that live inside
 * a normal module. It can publish data and be notified when new internal
 * data has been received via InternalPipe.
 */
class InternalThread : protected Publisher {
public:
	virtual ~InternalThread() {
		close();
	}
	
	void start() {
		init();
		thread = std::thread(&InternalThread::entry, this);
	}
	
	void stop() {
		{
			std::lock_guard<std::mutex> lock(mutex);
			do_run = false;
		}
		notify();
	}
	
	void join() {
		if(thread.joinable()) {
			thread.join();
		}
	}
	
	void close() {
		stop();
		join();
	}
	
	/*
	 * Can be overridden in user class. Needs to be thread-safe!
	 */
	virtual void notify() {
		std::lock_guard<std::mutex> lock(mutex);
		notify_counter++;
		condition.notify_all();
	}
	
protected:
	std::mutex mutex;
	
	bool do_run = true;
	
	/*
	 * Will be called from the parent thread before starting this thread
	 * to ensure initialization is done before starting another module.
	 */
	virtual void init() {}
	
	/*
	 * Main thread function.
	 */
	virtual void main() = 0;
	
	/*
	 * Wait for new data to be available. User needs to notify this module.
	 */
	void wait() {
		std::unique_lock<std::mutex> lock(mutex);
		while(consume_count == notify_counter) {
			condition.wait(lock);
		}
		consume_count = notify_counter;
	}
	
private:
	void entry() {
		main();
	}
	
private:
	std::thread thread;
	std::condition_variable condition;
	uint64_t notify_counter = 0;
	uint64_t consume_count = 0;
	
};


} // vnx

#endif // INCLUDE_VNX_INTERNALTHREAD_H

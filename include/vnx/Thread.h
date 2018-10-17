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

/** \brief A base class for light-weight worker threads.
 * 
 * Used in cases where a Module is too much.
 */
class Thread : protected Subscriber, protected Publisher {
public:
	/// Creates new thread with given name
	Thread(const std::string& vnx_name_);
	
	~Thread();
	
	/// Start thread in background. Safe to call multiple times.
	void start();
	
	/// Wait for thread to finish and join, if thread is still running. (thread-safe)
	void join();
	
	/// Trigger thread to exit and then join it, if thread is still running. (thread-safe)
	void stop();
	
protected:
	std::string vnx_name;
	
	/**
	 * Will be called from inside start() to ensure initialization is done before
	 * calling thread continues.
	 */
	virtual void init() {}
	
	/**
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

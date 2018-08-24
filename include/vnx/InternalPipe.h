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

#ifndef INCLUDE_VNX_INTERNALPIPE_H
#define INCLUDE_VNX_INTERNALPIPE_H

#include <mutex>
#include <vector>
#include <memory>


namespace vnx {

/*
 * InternalPipe can be used to communicate with InternalThread.
 * It is a thread-safe single producer single consumer queue.
 */
template<typename T>
class InternalPipe {
public:
	InternalPipe() {
		queue.reset(new std::vector<T>());
	}
	
	void push(const T& sample) {
		std::lock_guard<std::mutex> lock(mutex);
		queue->push_back(sample);
	}
	
	template<typename Iter>
	void insert(Iter begin, Iter end) {
		std::lock_guard<std::mutex> lock(mutex);
		queue->insert(queue->end(), begin, end);
	}
	
	std::unique_ptr<std::vector<T>> pop_all() {
		std::lock_guard<std::mutex> lock(mutex);
		std::unique_ptr<std::vector<T>> result(queue.release());
		queue.reset(new std::vector<T>());
		return result;
	}
	
private:
	std::mutex mutex;
	std::unique_ptr<std::vector<T>> queue;
	
};


} // vnx

#endif // INCLUDE_VNX_INTERNALPIPE_H

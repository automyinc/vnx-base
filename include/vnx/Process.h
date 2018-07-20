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

#ifndef INCLUDE_VNX_PROCESS_H_
#define INCLUDE_VNX_PROCESS_H_

#include <vnx/Value.h>
#include <vnx/Time.h>
#include <vnx/Publisher.h>
#include <vnx/ProcessBase.hxx>
#include <vnx/LogMsg.hxx>

#include <mutex>
#include <condition_variable>
#include <atomic>


namespace vnx {

/*
 * Initialize the process. Needs to be done first before creating any Modules.
 */
void init(const std::string& process_name, int argc, char** argv, std::map<std::string, std::string> options = {});

/*
 * Returns true if the process should continue to run.
 */
bool do_run();

/*
 * Wait for the the whole process and all modules to finish and shutdown.
 */
void wait();

/*
 * Trigger shutdown and wait for the the whole process and all modules to finish and shutdown.
 */
void close();

/*
 * Get the local process name.
 */
std::string get_process_name();

/*
 * Triggers all modules to shut down. Returns immediately.
 */
void trigger_shutdown();

/*
 * Force the process to exit, without waiting for modules to shut down. Returns immediately.
 */
void force_shutdown();


class Process : public ProcessBase {
public:
	Process(const std::string& name);
	
	~Process();
	
protected:
	std::string get_name() const;
	
	TimeSync get_sync_time() const;
	
	TopicInfoList get_topic_info() const;
	
	void pause_log();
	
	void resume_log();
	
	void set_debug(const int32_t& level);
	
	void close();
	
	void init();
	
	void main();
	
	void handle(std::shared_ptr<const vnx::LogMsg> value);
	
	void handle(std::shared_ptr<const TimeControl> value);
	
	void handle(std::shared_ptr<const TimeSync> value);
	
	void update_topic_info();
	
private:
	int is_log_paused = 0;
	
};


namespace process {
	
	extern std::mutex mutex;
	extern std::condition_variable condition;
	extern std::atomic<int> num_modules;
	
} // process


} // vnx

#endif /* INCLUDE_VNX_PROCESS_H_ */

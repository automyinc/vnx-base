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

/** \brief Initialize the process and parse command line arguments.
 * 
 * Needs to be called first before creating any Modules.
 * 
 * There are two different formats for \p option:
 * - A mapping from short option to long option, like "n" => "node".
 * - Providing a description for a long option, like "node" => "server address".
 * 
 * The following options are already internally used:
 * - "h" => "help" (prints help and exits)
 * - "c" => "config" (a config root directory, multiple possible, loaded left to right)
 * - "d" => "debug" (flag)
 * 
 * Additional config options:
 * - "vnx_type_map": A string map that for each entry [<alias type name>, <existing type name>] creates a mapping from an old (and no longer existing) type to a new type.
 * - "vnx_server_map": A string map that for each entry [<module name>, <server url>] a vnx::Server is spawned in the background.
 * - "vnx_proxy_map": A string map that for each entry [<module name>, <endpoint url>] a vnx::Proxy is spawned in the background.
 * 
 * @param process_name Name for this process
 * @param options List of options, see above for info.
 */
void init(const std::string& process_name, int argc, char** argv, std::map<std::string, std::string> options = {});

/// Returns true if the process should continue to run.
bool do_run();

/// Wait for the the whole process and all modules to finish and shutdown.
void wait();

/// Trigger shutdown and wait for the the whole process and all modules to finish and shutdown.
void close();

/// Get the local process name.
std::string get_process_name();

/// Get the local process id.
Hash64 get_process_id();

/// Triggers all modules to shut down. Returns immediately.
void trigger_shutdown();

/// Force the process to exit, without waiting for modules to shut down. Returns immediately.
void force_shutdown();


/** \brief A Module that handles process specific tasks.
 * 
 * Will be created and started in the background during vnx::init().
 * 
 * Displays log messages, handles time control and synchronization, etc.
 */
class Process : public ProcessBase {
public:
	explicit Process(const std::string& name);
	
	~Process() override;
	
protected:
	std::string get_name() const override;
	
	TimeSync get_sync_time() const override;
	
	std::vector<TopicInfo> get_topic_info() const override;

	std::vector<ModuleInfo> get_module_info() const override;
	
	ProcessInfo get_process_info() const override;

	Variant vnx_get_global_config(const std::string& key) const override;

	void vnx_set_global_config(const std::string& key, const Variant& value) override;

	void pause_log() override;
	
	void resume_log() override;
	
	void set_debug(const int32_t& level) override;
	
	void trigger_shutdown() override;
	
	void init() override;
	
	void main() override;
	
	void handle(std::shared_ptr<const LogMsg> value) override;
	
	void handle(std::shared_ptr<const TimeControl> value) override;
	
	void handle(std::shared_ptr<const TimeSync> value) override;
	
	void handle(std::shared_ptr<const ModuleInfo> value) override;
	
	void update_topic_info();
	
private:
	int is_log_paused = 0;
	
	std::map<Hash64, std::shared_ptr<const ModuleInfo>> module_info_map;
	
};


namespace process {
	
	extern std::mutex mutex;
	extern std::condition_variable condition;
	extern std::atomic<int> num_modules;
	
} // process


} // vnx

#endif /* INCLUDE_VNX_PROCESS_H_ */

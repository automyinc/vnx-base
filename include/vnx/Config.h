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

#ifndef INCLUDE_VNX_CONFIG_H_
#define INCLUDE_VNX_CONFIG_H_

#include <vnx/Input.h>
#include <vnx/Output.h>


namespace vnx {

/// Returns config value for key \p key, returns null in case no such key.
std::shared_ptr<std::string> get_config(const std::string& key);

/// Set config value (in-memory)
void set_config(const std::string& key, const std::string& value);

/// Read config file system tree starting at \p root_path
void read_config_tree(const std::string& root_path);

/** \brief Reads config value for key \p key.
 * 
 * Returns true if config is available, otherwise returns false and leaves \p value untouched.
 */
template<typename T>
bool read_config(const std::string& key, T& value) {
	std::shared_ptr<std::string> result = get_config(key);
	if(result) {
		from_string(*result, value);
		return true;
	}
	return false;
}

/// Set config value (in-memory)
template<typename T>
void write_config(const std::string& key, const T& value) {
	set_config(key, to_string(value));
}


} // vnx

#endif /* INCLUDE_VNX_CONFIG_H_ */

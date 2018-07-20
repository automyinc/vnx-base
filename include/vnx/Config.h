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

std::shared_ptr<std::string> get_config(const std::string& key);

void set_config(const std::string& key, const std::string& value);

void read_config_tree(std::string config_path);

template<typename T>
bool read_config(const std::string& key, T& value) {
	std::shared_ptr<std::string> result = get_config(key);
	if(result) {
		from_string(*result, value);
		return true;
	}
	return false;
}

template<typename T>
void write_config(const std::string& key, const T& value) {
	set_config(key, to_string(value));
}


} // vnx

#endif /* INCLUDE_VNX_CONFIG_H_ */

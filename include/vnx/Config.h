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

#include <vnx/Type.h>
#include <vnx/Variant.h>
#include <vnx/Object.h>


namespace vnx {

/// Returns config value for key \p key, returns empty in case no such key.
Variant get_config(const std::string& key);

/// Returns a config object for all sub-keys in the given namespace.
Object get_config_object(const std::string& name_space);

/// Set config value (in-memory)
void set_config(const std::string& key, const Variant& value);

/// Set config value via JSON string (in-memory)
void set_config(const std::string& key, const std::string& value);

/// Read config file system tree starting at \p root_path
void read_config_tree(const std::string& root_path);


} // vnx

#endif /* INCLUDE_VNX_CONFIG_H_ */

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

#ifndef INCLUDE_VNX_MEMORY_HPP_
#define INCLUDE_VNX_MEMORY_HPP_

#include <vnx/Memory.h>


namespace vnx {

inline
void Memory::chunk_t::alloc(size_t num_bytes, bool allow_short) {
	if(num_bytes & SHORT_BIT) {
		throw std::runtime_error("num_bytes & SHORT_BIT != 0");
	}
	size_ = num_bytes;
	if(num_bytes > SHORT_SIZE || !allow_short) {
		data_ = (char*)::malloc(num_bytes);
	} else {
		size_ |= SHORT_BIT;
	}
}

inline
void Memory::chunk_t::free() {
	if(!is_short()) {
		::free(data_);
	}
}


} // vnx

#endif /* INCLUDE_VNX_MEMORY_HPP_ */

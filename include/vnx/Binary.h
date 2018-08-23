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

#ifndef INCLUDE_VNX_BINARY_H_
#define INCLUDE_VNX_BINARY_H_

#include <vnx/Value.h>
#include <vnx/Memory.h>
#include <vnx/InputStream.h>
#include <vnx/OutputStream.h>


namespace vnx {

class Binary : public Value {
public:
	Memory data;
	const TypeCode* type_code = 0;
	
	typedef vnx::Value Super;
	
	static const Hash64 VNX_TYPE_HASH;
	static const Hash64 VNX_CODE_HASH;
	
	Binary();
	~Binary();
	
	Hash64 get_type_hash() const;
	const char* get_type_name() const;
	
	static std::shared_ptr<Binary> create();
	std::shared_ptr<Value> clone() const;
	
	void read(TypeInput& in, const TypeCode* type_code, const uint16_t* code);
	void write(TypeOutput& out, const TypeCode* type_code, const uint16_t* code) const;
	
	void read(std::istream& in);
	void write(std::ostream& out) const;
	
	void accept(Visitor& visitor) const;
	
	void clear();
	
};


class BinaryInputStream : public MemoryInputStream {
public:
	BinaryInputStream(const Binary* binary) : MemoryInputStream(&binary->data) {}
};

class BinaryOutputStream : public MemoryOutputStream {
public:
	BinaryOutputStream(Binary* binary) : MemoryOutputStream(&binary->data) {}
};


void read(TypeInput& in, vnx::Binary& binary, const TypeCode* type_code, const uint16_t* code);

void write(TypeOutput& out, const vnx::Binary& binary, const TypeCode* type_code, const uint16_t* code);

void accept(Visitor& visitor, const vnx::Binary& binary);


} // vnx

#endif /* INCLUDE_VNX_BINARY_H_ */

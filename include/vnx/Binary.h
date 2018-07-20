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
#include <vnx/InputStream.h>
#include <vnx/OutputStream.h>


namespace vnx {

class Binary : public Value {
public:
	struct chunk_t {
		char* data = 0;
		size_t size = 0;
	};
	
	const TypeCode* type_code = 0;
	std::vector<chunk_t> chunks;
	size_t size = 0;
	
	typedef vnx::Value Super;
	
	static const Hash64 VNX_TYPE_HASH;
	static const Hash64 VNX_CODE_HASH;
	
	Binary();
	Binary(const Binary& other);
	
	~Binary();
	
	Binary& operator=(const Binary& other);
	
	Hash64 get_type_hash() const;
	const char* get_type_name() const;
	
	static std::shared_ptr<Binary> create();
	std::shared_ptr<Value> clone() const;
	
	void read(TypeInput& in, const TypeCode* type_code, const uint16_t* code);
	void write(TypeOutput& out, const TypeCode* type_code, const uint16_t* code) const;
	
	void read(std::istream& in);
	void write(std::ostream& out) const;
	
	void accept(Visitor& visitor) const;
	
	char* add_chunk(size_t len);
	void clear();
	
};


class BinaryOutputStream : public OutputStream {
public:
	BinaryOutputStream(Binary* binary) : binary(binary) {}
	
	void write(const void* buf, size_t len) {
		::memcpy(binary->add_chunk(len), buf, len);
	}
	
	size_t get_output_pos() const {
		return binary->size;
	}
	
private:
	Binary* binary;
	
};


class BinaryInputStream : public InputStream {
public:
	BinaryInputStream(const Binary* binary) : binary(binary) {}
	
	size_t read(void* buf, size_t len) {
		if(chunk_index >= binary->chunks.size()) {
			return 0;
		}
		Binary::chunk_t chunk = binary->chunks[chunk_index];
		size_t left = chunk.size - pos;
		if(len > left) {
			len = left;
		}
		::memcpy(buf, chunk.data + pos, len);
		pos += len;
		if(pos == chunk.size) {
			chunk_index++;
			pos = 0;
		}
		return len;
	}
	
private:
	const Binary* binary;
	size_t chunk_index = 0;
	size_t pos = 0;
	
};


void read(TypeInput& in, vnx::Binary& binary, const TypeCode* type_code, const uint16_t* code);

void write(TypeOutput& out, const vnx::Binary& binary, const TypeCode* type_code, const uint16_t* code);

void accept(Visitor& visitor, const vnx::Binary& binary);


} // vnx

#endif /* INCLUDE_VNX_BINARY_H_ */

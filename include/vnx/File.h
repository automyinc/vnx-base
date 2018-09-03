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

#ifndef INCLUDE_VNX_FILE_H
#define INCLUDE_VNX_FILE_H

#include <vnx/Input.h>
#include <vnx/Output.h>

#include <cstdio>


namespace vnx {

class File {
public:
	TypeInput in;
	TypeOutput out;
	
	File();
	
	File(const std::string& path);
	
	File(const File&) = delete;
	
	~File();
	
	File& operator=(const File&) = delete;
	
	void open(const std::string& mode);
	
	void open(const std::string& path, const std::string& mode);
	
	uint16_t read_header();
	
	void write_header();
	
	void seek_begin();
	
	void seek_end();
	
	void seek_to(int64_t pos);
	
	std::string get_path() const {
		return path_;
	}
	
	size_t get_input_pos() const {
		return in.get_input_pos();
	}
	
	size_t get_output_pos() const {
		return out.get_output_pos();
	}
	
	void flush();
	
	void close();
	
private:
	::FILE* p_file = 0;
	std::string path_;
	
	FileInputStream stream_in;
	FileOutputStream stream_out;
	
};


} // vnx

#endif // INCLUDE_VNX_FILE_H

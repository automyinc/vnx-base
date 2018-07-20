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

#ifndef INCLUDE_VNX_RECORDWRITER_H_
#define INCLUDE_VNX_RECORDWRITER_H_

#include <vnx/Sample.hxx>
#include <vnx/RecordHeader.hxx>
#include <vnx/RecordIndex.hxx>
#include <vnx/OutputStream.h>


namespace vnx {

class RecordWriter {
public:
	/*
	 * Creates a new record writer, writing to a file given by "filename".
	 * Will truncate an already existing file.
	 * "header_size" is the maximum size of the header that is reserved at the beginning of the file.
	 * "block_size" is the size of each block in terms of number of samples.
	 * Bigger blocks increase read performance at the expense of increased write overhead (caused by repeated calls to flush()).
	 */
	RecordWriter(const std::string& filename, int32_t header_size = 262144, int32_t block_size = 4096);
	
	~RecordWriter();
	
	/*
	 * Write a new sample to the file.
	 */
	void write(std::shared_ptr<const Sample> sample);
	
	/*
	 * Rewrite the header and the current index and then flush the file.
	 * Used to limit data loss in case of a crash.
	 */
	void flush();
	
	/*
	 * Close the file.
	 */
	void close();
	
	/*
	 * Get the record header.
	 */
	const RecordHeader& get_header() const;
	
	/*
	 * Get the current byte position.
	 */
	size_t get_output_pos() const;
	
protected:
	void write_header();
	
	void write_index();
	
	void add_block();
	
private:
	FILE* file = 0;
	FileOutputStream stream;
	TypeOutput out;
	
	RecordHeader header;
	int64_t header_start_pos = -1;
	
	std::shared_ptr<RecordIndex> curr_block;
	int32_t index_pos = 0;
	int64_t curr_block_pos = -1;
	int64_t curr_out_pos = -1;
	int64_t last_sample_time = 0;
	
	std::unordered_map<uint64_t, record_topic_info_t> topic_info_map;
	std::unordered_map<uint64_t, uint64_t> sample_seq_map;
	
};


} // vnx

#endif /* INCLUDE_VNX_RECORDWRITER_H_ */

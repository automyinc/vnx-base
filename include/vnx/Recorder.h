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

#ifndef INCLUDE_VNX_RECORDER_H_
#define INCLUDE_VNX_RECORDER_H_

#include <vnx/RecorderBase.hxx>
#include <vnx/ProxyClient.hxx>
#include <vnx/RecordWriter.h>
#include <vnx/Time.h>


namespace vnx {

class Recorder : public RecorderBase {
public:
	Recorder(const std::string& _vnx_name = "Recorder");
	
protected:
	void init();
	
	void main();
	
	void handle(std::shared_ptr<const Sample> sample);
	
	void flush();
	
	void print_stats();
	
private:
	std::shared_ptr<RecordWriter> writer;
	std::shared_ptr<ProxyClient> proxy;
	
	int64_t last_output_pos = 0;
	int64_t last_sample_count = 0;
	
};


} // vnx

#endif /* INCLUDE_VNX_RECORDER_H_ */

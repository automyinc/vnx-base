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

#ifndef INCLUDE_VNX_TIME_H_
#define INCLUDE_VNX_TIME_H_

#include <vnx/TimeControl.hxx>
#include <vnx/TimeSync.hxx>


namespace vnx {

int64_t get_time_seconds();				// current virtual time in seconds
int64_t get_time_millis();				// current virtual time in milli-seconds
int64_t get_time_micros();				// current virtual time in micro-seconds

int64_t get_sync_time_micros();			// current sync time in micro-seconds

int64_t get_wall_time_seconds();		// current wall time in seconds
int64_t get_wall_time_millis();			// current wall time in milli-seconds
int64_t get_wall_time_micros();			// current wall time in micro-seconds
int64_t get_wall_time_nanos();			// current wall time in nano-seconds

std::string get_date_string(bool UTC = false, int64_t time_secs = -1);
std::string get_date_string_ex(const char* format, bool UTC = false, int64_t time_secs = -1);

TimeControl get_time_control();

void set_time_control(const TimeControl& state);

TimeSync get_time_sync();

void set_time_sync(const TimeSync& state);


class Timer {
public:
	/*
	 * Reset the timer using "now" as the current time.
	 */
	void reset(int64_t now) {
		is_active = true;
		deadline = now + interval;
	}
	
	/*
	 * Stop this timer.
	 */
	void stop() {
		is_active = false;
	}
	
	int64_t interval = 0;			// timer interval in micro-seconds
	int64_t deadline = 0;			// time (in usec) when the timer will expire
	
	bool is_repeat = false;
	bool is_active = false;
	
	std::function<void()> func;		// user callback function
	
};


} // vnx

#endif /* INCLUDE_VNX_TIME_H_ */

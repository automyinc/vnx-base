
/** \page tutorial_simple_publish Simple publish
 * 
 * In this tutorial we will publish some samples and inspect them at run-time:
 * 
 * \include doc/tutorials/simple_publish.cpp
 * 
 * vnx::Publisher is used to publish samples (ie. instances of vnx::Sample). A sample contains various information such as the topic on which
 * it is published, in addition to the sample value (a vnx::Value).
 * 
 * Publisher will wrap the given value in a vnx::Sample, attach its identity and a sequence number and then publish the sample on the given topic.
 * 
 * In addition we are using the VNX logging system to log some INFO messages. Internally, for each message a vnx::LogMsg sample
 * is published on "vnx.log_out", which are then printed to std::cout by the background vnx::Process (depending on the log level).
 * 
 * The code can be compiled with:
 * \code
 * g++ -o simple_publish simple_publish.cpp -std=c++11 -lvnx_base
 * \endcode
 * 
 * vnx::Terminal is a module that implements an interactive command prompt to inspect data in the local process at run-time.
 * 
 * Pressing enter in the console will activate the Terminal's command prompt:
 * \code
$ ./simple_publish 
[simple_publish] INFO: Published a vnx::Marker with time 1539840297890

Help: quit | debug <level> | errors | topic <expr> | grep <expr> | spy [expr] | dump [expr]
Terminal: 
 * \endcode
 * 
 * Logging output will be paused as long as the Terminal is activated. It's important to always use the VNX logging system instead of
 * printing to std::cout directly, otherwise it will be difficult to use the Terminal.
 * 
 * First let's take a look at the topics in the local process (ie. simple_publish itself):
 * \code
Terminal: t

test.topic                     : 0 subscribers, 10 samples
vnx.log_out                    : 2 subscribers, 4 samples
vnx.module_info                : 0 subscribers, 0 samples
vnx.shutdown                   : 2 subscribers, 0 samples
vnx.time_control               : 2 subscribers, 0 samples
vnx.time_sync                  : 1 subscribers, 0 samples
vnx.topic_info                 : 0 subscribers, 761 samples
 * \endcode
 * 
 * "t" is a shortcut for the "topic" command and without an \p expr given it will show statistics for all topics.
 * We can see our "test.topic" as well as a number of internal topics which are used by VNX itself.
 * See vnx::Terminal documentation for more information on its commands.
 * 
 * After pressing enter again we return back to normal mode and logging output is resumed.
 * 
 * Now let's take a look at our "test.topic" samples by again pressing enter and this time using the "dump" command:
 * \code
Help: quit | debug <level> | errors | topic <expr> | grep <expr> | spy [expr] | dump [expr]
Terminal: dump test.topic
1539841189981599 14 test.topic -> vnx.Marker {
  "time": 1539841189981,
  "message": "Hello World!"
}
1539841190981826 15 test.topic -> vnx.Marker {
  "time": 1539841190981,
  "message": "Hello World!"
}
 * \endcode
 * 
 * The "dump" command will print samples for matching topics.
 * For each sample we get the timestamp (synchronized time in [usec]), the sequence number, the topic name as well as the sample's value type:
 * \code
1539841189981599 14 test.topic -> vnx.Marker {
 * \endcode 
 * 
 * Followed by the sample's value as pretty printed JSON, as seen above.
 * 
 * After pressing enter again we return back to normal mode again.
 * 
 */

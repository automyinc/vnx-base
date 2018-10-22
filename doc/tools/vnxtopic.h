
/** \page vnxtopic vnxtopic
 * 
 * \code
 * vnxtopic [-n | --node <url>]
 * \endcode
 * 
 * vnxtopic is a commandline tool to show topic info for a given node.
 * 
 * By default it will connect to localhost:4444, otherwise to the process given by the \p --node argument.
 * 
 * Example:
 * \code
$ vnxtopic -n example.sock
test.topic                     : 0 subscribers, 10 samples
vnx.log_out                    : 2 subscribers, 4 samples
vnx.topic_info                 : 0 subscribers, 761 samples
 * \endcode
 * 
 */

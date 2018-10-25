
/** \page vnxtimeserver vnxtimeserver
 * 
 * vnxtimeserver is a process that serves as a time server for other processes on other machines to connect to and sync their time.
 * 
 * \code
 * Usage: vnxtimeserver [-p | --port <port>] [-s | --source <url>]
 * \endcode
 * 
 * - \b -p or \b --port TCP server port, default = 5555.
 * - \b -s or \b --source Optional time source, ie. another vnxtimeserver running on another machine, by default takes the local system time as source.
 * 
 * Any VNX process can serve as a time source, vnxtimeserver is only a separate stand-alone version.
 * 
 * When creating a vnx::Proxy to connect to another process it can be configured to also sync time with the other process, ie. making the other process a time server.
 * This is achieved with the \p time_sync configuration flag or by importing the special topic "vnx.time_sync".
 * 
 */


/** \page vnxclose vnxclose
 * 
 * vnxclose is a tool to shutdown a VNX process remotely. It is the same as calling vnx::trigger_shutdown().
 * 
 * \code
 * Usage: vnxclose [-n | --node <url>]
 * \endcode
 * 
 * - \b n or \b --node Target process to shut down.
 * 
 * Example:
 * \code
$ vnxclose -n localhost
Closed process 'vnxplay'
 * \endcode
 * 
 */

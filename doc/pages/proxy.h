
/** \page proxy Proxy
 * 
 * vnx::Proxy is a module that connects to a vnx::Server running in another process via TCP or UNIX domain socket.
 * 
 * It can be used to import and export topics from/to the other process. The vnx::Server on the other end may also be configured
 * to export certain topics by itself.
 * 
 * Users in VNX can create arbitrary network topologies by using a combination of servers and proxies. Care has to be taken not to create loops however.
 * 
 * Typically each process has at least one Server (to allow other processes to connect) and one Proxy to import data from another process,
 * most likely from a \ref vnxrouter or from a \ref vnxplay instance.
 * 
 * See vnx::Proxy for more information.
 * 
 */

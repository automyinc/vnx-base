
/** \page server Server
 * 
 * vnx::Server is a module that accepts connections from other processes via TCP or UNIX domain socket.
 * 
 * It can be configured to export certain topics to all client processes. See vnx::Server for more information.
 * 
 * For each connection a vnx::Proxy is spawned that handles the processing of data.
 * 
 * Typically a vnx::Proxy is used to connect to a vnx::Server.
 * 
 * Tools such as \ref vnxtopic, \ref vnxdump, \ref vnxclose, \ref vnxrecord and \ref vnxgraph need a vnx::Server to connect to.
 * 
 */

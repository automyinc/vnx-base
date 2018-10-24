
/** \page topic Topic
 * 
 * A Topic is defined by its name which is a string that defines a leaf node inside a tree, just like a file path but with "." instead of "/" separating the levels.
 * 
 * For example: "sensors.raw_data.Camera_A"
 * 
 * Multiple different types can be published on the same topic without them being specified beforehand.
 * 
 * Modules can subscribe to specific topics as well as higher level nodes like "sensors.raw_data" or even "sensors", it will then receive all samples published in that sub-tree.
 * 
 * Modules can subscribe to any number of topics as well as publish samples on any topic.
 * Subscriptions are reference counted, which means if a module subscribes twice to the same topic it needs to unsubscribe twice to stop receiving samples on said topic.
 * 
 * Topics are global within a process and need to be imported and/or exported from/to other processes. This is achieved with the vnx::Proxy, vnx::Server and vnx::Router.
 * 
 */

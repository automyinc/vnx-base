
/** \page vnxgraph vnxgraph
 * 
 * vnxgraph is a tool that creates a dot graph for one or more processes.
 * 
 * \code
 * Usage: vnxgraph [-n | --nodes <list of node urls>]
 * \endcode
 * 
 * - \b -n or \b --nodes List of processes to connect to and include in the graph.
 * 
 * Example:
 * \code
$ vnxgraph -n ~/automy-website/vnxwebserver.sock 
digraph vnxgraph {
  compound = true;
  concentrate = true;
  splines = true;
  subgraph cluster_6bbf5f0268ecb3be {
    label = "vnxwebserver";
    labeljust = "l";
    "6bbf5f0268ecb3be" [shape=point, style=invis];
    "0ca1728d9fac7aab" [label="HttpProcessor", style=filled, fillcolor=lightgrey, shape=box];
    "server.http.request" -> "0ca1728d9fac7aab" [color=red3];
    "server.http.processor" -> "0ca1728d9fac7aab" [color=red3];
    "0ca1728d9fac7aab" -> "server.http.response" [color=blue3];
    "0ca1728d9fac7aab" -> "server.cache.request" [color=blue3];
    "278639d58aa25856" [label="HttpParser", style=filled, fillcolor=lightgrey, shape=box];
    "server.frontend.client_data" -> "278639d58aa25856" [color=red3];
    "278639d58aa25856" -> "server.http.request" [color=blue3];
    "565bf00841c2720a" [label="ViewProcessor", style=filled, fillcolor=lightgrey, shape=box];
    "server.dynamic.request" -> "565bf00841c2720a" [color=red3];
    "server.dynamic.channel" -> "565bf00841c2720a" [color=red3];
    "565bf00841c2720a" -> "server.cache.channel" [color=blue3];
    "565bf00841c2720a" -> "server.cache.request" [color=blue3];
    "565bf00841c2720a" -> "server.domain" [color=blue3];
    "5752a09a927a8de8" [label="ViewProcessor", style=filled, fillcolor=lightgrey, shape=box];
    "server.default.request" -> "5752a09a927a8de8" [color=red3];
    "server.default.channel" -> "5752a09a927a8de8" [color=red3];
    "5752a09a927a8de8" -> "server.domain" [color=blue3];
    "622d685fd9f1df06" [label="ViewProcessor", style=filled, fillcolor=lightgrey, shape=box];
    "server.page.request" -> "622d685fd9f1df06" [color=red3];
    "server.page.channel" -> "622d685fd9f1df06" [color=red3];
    "622d685fd9f1df06" -> "server.cache.channel" [color=blue3];
    "622d685fd9f1df06" -> "server.domain" [color=blue3];
    "622d685fd9f1df06" -> "server.cache.request" [color=blue3];
    "6c44f408ec8788f6" [label="Terminal", style=filled, fillcolor=lightgrey, shape=box];
    "7d7b0aff9eeded4e" [label="Database", style=filled, fillcolor=lightgrey, shape=box];
    "ac624d19bb04cd68" [label="Frontend", style=filled, fillcolor=lightgrey, shape=box];
    "baf72d37c75b5ba8" [label="FileSystem", style=filled, fillcolor=lightgrey, shape=box];
    "server.filesystem.request" -> "baf72d37c75b5ba8" [color=red3];
    "baf72d37c75b5ba8" -> "server.cache.channel" [color=blue3];
    "baf72d37c75b5ba8" -> "server.domain" [color=blue3];
    "bc08a51054844bcd" [label="Cache", style=filled, fillcolor=lightgrey, shape=box];
    "server.cache.channel" -> "bc08a51054844bcd" [color=red3];
    "server.cache.request" -> "bc08a51054844bcd" [color=red3];
    "server.domain" -> "bc08a51054844bcd" [color=red3];
    "bc08a51054844bcd" -> "server.page.request" [color=blue3];
    "bc08a51054844bcd" -> "server.http.processor" [color=blue3];
    "bc08a51054844bcd" -> "server.page.channel" [color=blue3];
    "bc08a51054844bcd" -> "server.domain" [color=blue3];
    "bc08a51054844bcd" -> "server.dynamic.request" [color=blue3];
    "bc08a51054844bcd" -> "server.filesystem.request" [color=blue3];
    "bc08a51054844bcd" -> "server.dynamic.channel" [color=blue3];
    "bfbfc459e7d27107" [label="DatabaseView", style=filled, fillcolor=lightgrey, shape=box];
    "server.database.request" -> "bfbfc459e7d27107" [color=red3];
    "bfbfc459e7d27107" -> "server.domain" [color=blue3];
    "c462364c786f381a" [label="Server", style=filled, fillcolor=lightgrey, shape=box];
    "f4dd7aff6c492cb9" [label="HttpRenderer", style=filled, fillcolor=lightgrey, shape=box];
    "server.http.response" -> "f4dd7aff6c492cb9" [color=red3];
    "f4dd7aff6c492cb9" -> "server.frontend.return_data" [color=blue3];
  }
}
 * \endcode
 * 
 * Which can then be turned into an SVG image as follows:
 * \code
 * vnxgraph -n ~/automy-website/vnxwebserver.sock | dot -Tsvg > graph.svg
 * \endcode
 * 
 * Example:
 * \image html doc/diagrams/vnxwebserver_graph.svg width=100%
 * 
 */

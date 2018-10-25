
/** \page vnxdump vnxdump
 * 
 * \code
 * vnxdump [-1 | --one] [-i | --info] [-s | --source <url>] [-t | --topic <expr>] [-x | --compact] [--max-list-size <size, 0=unlimited>]
 * \endcode
 * 
 * vnxdump prints the content of samples which are published in a process.
 * 
 * By default it connects to localhost:4444 and dumps the content of all samples in pretty printed JSON format.
 * 
 * The options are as follows:
 * - \b -1 or \b --one Flag if to print only one sample
 * - \b -i or \b --info Flag if to print only the header info
 * - \b -s or \b --source Node url to connect to
 * - \b -t or \b --topic Topic expression (sub-string) to search for, by default all topics are matched.
 * - \b -x or \b --compact Flag if to print in compact format instead of pretty print.
 * - \b --max-list-size Maximum size of arrays and maps, default = 1000.
 * 
 * For each sample a header is printed followed by the sample's value unless \b --info is given. The header format is as follows:
 * \code
{sync publish time stamp} {sequence number} {topic name} -> {value type name}
 * \endcode 
 * 
 * Example:
 * \code
$ vnxdump -s localhost -t module_info
1540236770548505 35 vnx.module_info -> vnx.ModuleInfo {
  "time": 1540236770548313,
  "id": 17652422822456569689,
  "src_mac": 4321875513216601026,
  "name": "vnxrouter",
  "type": "vnx.Process",
  "sub_topics": ["vnx.shutdown", "vnx.module_info", "vnx.log_out", "vnx.time_control", "vnx.time_sync"],
  "pub_topics": ["vnx.module_info", "vnx.log_out", "vnx.topic_info"],
  "remotes": []
}
1540236770548637 35 vnx.module_info -> vnx.ModuleInfo {
  "time": 1540236770548497,
  "id": 6549831085355615111,
  "src_mac": 11643684241314345935,
  "name": "Terminal",
  "type": "vnx.Terminal",
  "sub_topics": ["vnx.time_control", "vnx.log_out", "vnx.shutdown"],
  "pub_topics": ["vnx.module_info", "vnx.log_out"],
  "remotes": []
}
 * \endcode
 * 
 */

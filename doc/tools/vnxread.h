
/** \page vnxread vnxread
 * 
 * vnxread is a tool to print the contents of a VNX binary file as JSON.
 * 
 * \code
 * Usage: vnxread [-1 | --compact] [-f | --file <filename>] [-t | --type-only]
 * \endcode
 * 
 * - \b -1 or \b --compact Flag if to print compact JSON.
 * - \b -f or \b --file File name to read.
 * - \b -t or \b --type-only Flag if to print only the type names.
 * 
 * A file can consist of one or more serialized values (instances of vnx::Value).
 * 
 * Example:
 * \code
$ vnxread -f tutorials/Velodyne_FC.dat
{
  "time": 1529733584383320,
  "matrix": [-0.999707, 0.0219336, -0.01024, 0, -0.0219965, -0.99974, 0.00607594, 0, -0.010104, 0.0062994, 0.999929, 0, 3.45, 0, 0, 1],
  "position": [3.45, 0, 0],
  "rotation": [0.0060763, 0.0102401, 3.11966],
  "delay": 0
}
 * \endcode
 * 
 */

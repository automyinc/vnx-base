
/** \page tutorial_second_process Second VNX process
 * 
 * In this tutorial we will read back a file that was created in the previous tutorial \ref tutorial_first_process.
 * 
 * In addition we will use the config system to access command line arguments:
 * 
 * \include doc/tutorials/second_process.cpp
 * 
 * The code can be compiled with:
 * \code
 * g++ -o second_process second_process.cpp -std=c++11 -lvnx_base
 * \endcode
 * 
 * This time we didn't hard code the file name, instead we use a config value for it.
 * 
 * Using the \p options parameter to vnx::init() we can define multiple command line config options:
 * \code
$ ./second_process -h
Usage: second_process [-c | --config <directory>] [-d | --debug] [-f | --file <file name>] [-h | --help]
 * \endcode
 * 
 * As can be seen from the help message above there are already some built-in config options, including the \p --help option itself.
 * See vnx::init() documentation for more info on those.
 * 
 * Running the program will produce a compact JSON object (which is the default operator<<) and the additional message line:
 * \code
$ ./second_process -f test.dat
{"time": 1539835017627, "message": "Hello World!"}
Hello World! (10384 ms ago)
 * \endcode
 * 
 * Because we gave the \p --file option a default value we could also omit the command line parameter.
 * 
 */

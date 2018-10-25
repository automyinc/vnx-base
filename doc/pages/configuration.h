
/** \page configuration Configuration
 * 
 * VNX has a configuration system that reads configuration files as well as command line arguments.
 * 
 * Files can either be a JSON file (*.json) containing multiple values or a regular file containing one value.
 * 
 * Configuration files need to be in a folder which is passed to a VNX process via the \b -c or \b --config parameter.
 * Multiple folders can be specified which are parsed from left to right, potentially overwriting configuration options.
 * 
 * Command line options can be given on the command line as well as via a file in a config folder. Command line options always take preference over any configuration files.
 * 
 * Module configuration options are typically contained in a JSON file "ModuleName.json" in a config folder, but can also be given on the command line via \b --ModuleName.option <value>.
 * Alternatively, individual module configuration options can also be given as individual files in a folder "ModuleName/".
 * 
 * Configuration options are always parsed as JSON, with an exception that strings on the command line and in separate files do not need double quotes.
 * 
 * On the command line special rules apply:
 * - Strings need to be in double quotes if they contain white-space.
 * - Arrays can be specified by a list of values, for example --option 1 2 3 4 will result in an array [1, 2, 3, 4].
 * - Boolean options are set to 1 (ie. true) just by specifying the option, but can also be set to false by specifying a value of 0.
 * - In general any option can be given as a JSON string.
 * 
 * Example:
 * \code
$ find config/
config/
config/some_option => 1234
config/SomeModule.json => {"some_option": 1234}
config/AnotherModule
config/AnotherModule/some_option => 1234
 * \endcode
 * 
 * Consider the following code:
 * \code{.cpp}
int main(int argc, char** argv) {
	
	vnx::init("configuration_example", argc, argv);
	
	{
		std::string value = "default";
		vnx::read_config("some_option", value);
		std::cout << "INFO: some_option = '" << value << "'" << std::endl;
	}
	{
		std::string value = "default";
		vnx::read_config("SomeModule.some_option", value);
		std::cout << "INFO: SomeModule.some_option = '" << value << "'" << std::endl;
	}
	{
		std::string value = "default";
		vnx::read_config("AnotherModule.some_option", value);
		std::cout << "INFO: AnotherModule.some_option = '" << value << "'" << std::endl;
	}
	
	vnx::close();     // Shutdown (ensures clean exit)
}
 * \endcode
 * 
 * Example without any configuration:
 * \code
$ configuration_example
some_option = 'default'
SomeModule.some_option = 'default'
AnotherModule.some_option = 'default'
 * \endcode
 * 
 * Example with above "config" folder:
 * \code
$ configuration_example -c config/
INFO: some_option = '1234'
INFO: SomeModule.some_option = '1234'
INFO: AnotherModule.some_option = '1234'
 * \endcode
 * 
 * Example with "config" folder and command line options:
 * \code
$ configuration_example -c config/ --some_option 5 6 7 8 --SomeModule.some_option 4321 --AnotherModule.some_option
INFO: some_option = '8'
INFO: SomeModule.some_option = '4321'
INFO: AnotherModule.some_option = '1'
 * \endcode
 * 
 */

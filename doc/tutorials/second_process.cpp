#include <vnx/Process.h>        // Needed for vnx::init()
#include <vnx/Config.h>			// Needed for vnx::read_config()
#include <vnx/Input.h>          // Needed for vnx::read_from_file()
#include <vnx/Marker.hxx>       // Generated code has a *.hxx extension

int main(int argc, char** argv) {
	
	std::map<std::string, std::string> options;
	options["f"] = "file";                 // Shortcut definition
	options["file"] = "file name";         // Parameter definition with description for help (-h) message
	
	vnx::init("second_process", argc, argv, options);        // Initialize (ie. parse configs, etc.)
	
	std::string file_name = "test.dat";          // Default value in case config has not been set
	vnx::read_config("file", file_name);         // Tries to read the config value
	
	std::shared_ptr<vnx::Value> value = vnx::read_from_file(file_name);
	if(value) {
		std::cout << *value << std::endl;        // Will invoke virtual void Value::write(std::ostream& out)
	} else {
		std::cout << "Unable to read file!" << std::endl;
	}
	
	auto marker = std::dynamic_pointer_cast<vnx::Marker>(value);      // Let's see if it's what we expect it to be
	if(marker) {
		std::cout << marker->message << " (" << (vnx::get_time_millis() - marker->time) << " ms ago)" << std::endl;
	}
	
	vnx::close();     // Shutdown (ensures clean exit)
}

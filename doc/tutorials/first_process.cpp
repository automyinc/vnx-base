#include <vnx/Process.h>        // Needed for vnx::init()
#include <vnx/Output.h>         // Needed for vnx::write_to_file()
#include <vnx/Marker.hxx>       // Generated code has a *.hxx extension

int main(int argc, char** argv) {
	
	vnx::init("first_process", argc, argv);        // Initialize
	
	std::shared_ptr<vnx::Marker> value = vnx::Marker::create();
	value->time = vnx::get_time_micros();
	value->message = "Hello World!";
	
	vnx::write_to_file("test.dat", value);
	
	vnx::close();     // Shutdown (ensures clean exit)
}

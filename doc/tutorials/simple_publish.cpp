#include <vnx/Process.h>
#include <vnx/Terminal.h>
#include <vnx/Publisher.h>
#include <vnx/Marker.hxx>

#include <unistd.h>

int main(int argc, char** argv) {
	
	vnx::init("simple_publish", argc, argv);
	
	// We create a Terminal to inspect data at run-time on-demand
	vnx::Handle<vnx::Terminal> terminal = new vnx::Terminal("Terminal");
	terminal.start();
	
	// Get a pointer to our topic (will create new topic if not already existing)
	std::shared_ptr<vnx::Topic> topic = vnx::get_topic("test.topic");
	
	// We need a Publisher, each Publisher has a unique identity
	vnx::Publisher publisher;
	
	// Run until shutdown is triggered
	while(vnx::do_run()) {
		
		std::shared_ptr<vnx::Marker> value = vnx::Marker::create();
		value->time = vnx::get_time_millis();
		value->message = "Hello World!";
		
		publisher.publish(value, topic);     // Publish the value in zero-copy mode (ie. via std::shared_ptr)
		
		/*
		 * After publish() we can keep the sample value but we may not modify it anymore, since other threads
		 * could have and keep a pointer to the value forever.
		 */
		
		// Publish an info log message, VNX will print it to std::cout by default.
		vnx::log_info().out << "Published a vnx::Marker with time " << value->time;
		
		::usleep(1000 * 1000);
	}
	
	vnx::wait();     // Wait for clean shutdown
}

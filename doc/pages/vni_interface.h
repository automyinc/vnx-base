
/** \page vni_interface VNI (Virtual Network Interface)
 * 
 * The code generator (\ref vnxcppcodegen) reads interface type definitions written in "VNI" (Virtual Network Interface) with a file extension of "*.vni".
 * 
 * The language is similar to Java in its design, types are separated into packages and each type is contained in its own file with a matching file name.
 * 
 * \section class Class
 * 
 * Classes are like in Java, single inheritance is possible.
 * 
 * However there are no references, by default a field is directly embedded as in C++ or a pointer is used.
 * 
 * \code{.java}
package example;

import other_package.OtherType;

class ExampleType <extends SomeType> {
	
	bool value_a;			// boolean, default = 0 (FALSE)
	uchar value_b;			// unsigned 8-bit, default = 0
	ushort value_c;			// unsigned 16-bit, default = 0
	uint value_d;			// unsigned 32-bit, default = 0
	ulong value_e;			// unsigned 64-bit, default = 0
	char value_f;			// signed 8-bit, default = 0
	short value_g;			// signed 16-bit, default = 0
	int value_h;			// signed 32-bit, default = 0
	long value_i;			// signed 64-bit, default = 0
	float value_j;			// 32-bit float, default = 0.0
	double value_k;			// 64-bit float, default = 0.0
	
	int value_x = 1234;
	double value_y = 123.456;
	
	string value_m;					// dynamic string, default = ""
	string value_n = "default";
	
	float array_a[3];				// static array, default = {0,0,0}
	SomeType array_b[4];			// static array, default = {}
	
	SomeType value_o;				// nested type
	some_package.SomeType value_oo;	// nested type from other package
	
	vector<int> vector_a;			// dynamic array, default = {}
	vector<SomeType> vector_c;
	
	pair<int, SomeType> pair_a;		// like std::pair, default = {}
	
	map<int, SomeType> map_a;		// dynamic map, default = {}
	
	const SomeType* p_value;		// pointer to nested type, default = 0
	
	void update();					// user defined function
	double compute(int arg) const;	// user defined const function
	
	alias old_field new_field;		// alias definition, when renaming fields, goes both ways
	
}
 * \endcode
 * 
 * Fields are either primitive or extended, with primitive meaning their size is known at compile time and extended whose size is dynamic.
 * Integral types and static arrays of integral types are primitive, all other fields are extended.
 * 
 * Primitive fields are more efficient to serialize and de-serialize as well as more space efficient since their size is static.
 * Fields of integral type, of enum type or of type string can be given a default value in the VNI definition.
 * 
 * User defined functions have to be implemented in a separate *.cpp file and linked in by the user.
 * 
 * If a class does not have a user defined super-class (via extends) it will implicitly inherit from the internal vnx::Value class.
 * As such all classes have vnx::Value as their base class.
 * 
 * \section struct Struct
 * 
 * In addition to classes one can also define structs, the only difference is structs cannot inherit and they cannot be published by themselves, only when contained in a class.
 * 
 * The use-case for structs are small types which are used in large arrays, since a class has an overhead of 4 to 8 bytes per instance in memory.
 * 
 * \code{.java}
package example;

struct example_type_t {
	
	float x;
	float y;
	float z;
	
}
 * \endcode
 * 
 * \section enum Enum
 * 
 * Enums are like in Java, they are their own type and one cannot assign custom integer values.
 * 
 * Internally for each label a 32-bit integer value is created using the CRC64 hash of the name.
 * This allows for backwards compatibility when adding, removing or re-ordering enum values.
 * 
 * \code{.java}
package example;

enum transaction_type_e {
	
	CREDIT, DEBIT, TRANSFER
	
}
 * \endcode
 * 
 * Like structs, enums by themselves cannot be published, since they do not inherit from vnx::Value.
 * 
 * When defining an enum field a default value of 0 is assigned, unless a user defined value is given:
 * 
 * \code{.java}
class ExampleType {
	
	transaction_type_e type;				// default = 0
	transaction_type_e type_2 = CREDIT;		// default = CREDIT
	
}
 * \endcode
 * 
 * \section Module
 * 
 * Modules are defined in the interface to generate a base class `ModuleBase` from which the user can inherit,
 * as well as a client class `ModuleClient` which can be used to send requests.
 * 
 * Modules can subscribe to topics to receive data, publish data on topics as well as register themselves as a service and receive requests.
 * 
 * Each module has a main() function that is executed in its own thread. The only way to access a module is by sending requests to it.
 * 
 * \code{.java}
package example;

module ExampleModule {
	
	int config_a = 1234;			// config variable
	string config_b = "default";	// config variable
	SomeType config_c;				// config variable
	vector<float> config_d;			// config variable
	
	void handle(SomeType sample);	// handle function
	
	void do_something(int param_a, SomeType param_b); 	// request function
	
	int get_something() const;		// const request function
	
}
 * \endcode
 * 
 * Contrary to functions in C++ and Java one cannot overload functions, this is to allow for transparent compatibility.
 * 
 * Functions returning a value need to be const, this is such as to allow multiple re-tries in case a response was lost without violating consistency.
 * 
 * `void handle(SomeType sample)` functions are special in that they are called when the Module receives a sample of the specified type.
 * 
 * For the above example a base class `example::ExampleModuleBase` is generated from which the user inherits when implementing the actual `example::ExampleModule`.
 * For each configuration variable a public field is generated which can be accessed before the module is started. In the base class constructor the configuration variables are loaded from the config system.
 * 
 * For each `void handle(...)` function two functions are generated in the base class:
 * - A `void handle(std::shared_ptr<const example::SomeType> value)`
 * - A `void handle(std::shared_ptr<const example::SomeType> value, std::shared_ptr<const vnx::Sample> sample)`
 * 
 * The second function allows access to the sample itself, not just it's value.
 * By default the second function calls the first while ignoring the sample header. So when overriding the second function one has to remember that the first one will not be called anymore.
 * 
 * For each request function a pure virtual function is generated which has to be implemented by the user, it will be called when a request is received.
 * 
 * Additionally for the above example a client class called `example::ExampleModuleClient` will be generated which is a wrapper for serializing and de-serializing the requests and responses.
 * To the user it appears as if the functions are called directly on the module object but behind the scenes a request is created, sent to the module,
 * after which the calling thread is blocked until a response is received and then returned.
 * 
 * In case a request could not be processed an exception is thrown. This can happen when the requested service does not exist, is not reachable,
 * the requested function does not exist, the connection got interrupted or there was an exception when processing the request.
 * 
 * Moreover, for request functions that return void an optional asynchronous client function is generated with a "_async()" suffix.
 * This "async" version does not wait for completion of the request, which means the calling thread will not be blocked, but the user would also not know if the request was processed successfully.
 * 
 * \section package Package
 * 
 * For each package a special "package.vni" file can be used to define various package global types.
 * 
 * \code{.java}
package example;

topic some_topic;				// static topic definition of "example.some_topic"

extern UserType = {11, 4, 7};	// user defined type (with static type code)

typedef NewType OldType;		// just like in C++, only for VNI classes

 * \endcode
 * 
 * Static topics are mapped to a static vnx::TopicPtr, for example `std::shared_ptr<vnx::Topic> example::some_topic`.
 * 
 * `extern` can be used to define custom types which are entirely user defined, ie. no code is generated.
 * However the type code (see vnx::CODE_ARRAY, vnx::CODE_LIST, ...) needs to be defined as an array of integer codes.
 * The implementation is expected to be in a file "example/UserType.h".
 * 
 * `typedef` can be used to map an old type (which has been deleted) to a new type, or simply to define a type alias.
 * 
 * \section compatibility Compatibility
 * 
 * An important design feature is transparent compatibility between different versions of the same type.
 * This allows the usage of old recordings with new code or running different versions of software components at the same time.
 * 
 * Transparent compatibility covers the following use-cases:
 * - A field is added or removed to/from a class or struct. If data for a field is missing it will be left as default initialized. Any extra fields in the data are ignored.
 * - Changing a field of integral type to any other integral type, such as float to double or int to float. The conversion is done as specified in the C++ standard.
 * - Changing the size of a static array. Too many elements are ignored and missing elements are left as default initialized.
 * - Changing the type of a static array, vector or map. The behavior is the same as when changing the type of a field.
 * - Changing the parent class in case of inheritance. The behavior is the same as removing and adding fields.
 * - Adding, removing or re-ordering enum values.
 * - Different byte order, ie. little endian vs. big endian.
 * 
 * If a conversion cannot be applied the situation is handled as if the two fields (source and destination) have a different name.
 * In other words, it is impossible for an error to occur during de-serialization, the worst case scenario is data not being passed through.
 * It is up to the user to handle changes that cannot be covered transparently by the framework.
 * 
 * The same rules apply to request functions, which are nothing else than a struct named after the function with each parameter being a field.
 * This means parameters can be added, removed, re-ordered and their type can be changed according to above rules while still being transparently compatible.
 * 
 * \section limitations Limitations
 * 
 * - The maximum size of a static array is: VNX_MAX_STATIC_SIZE = 0xFFFF elements
 * - The maximum size of dynamic containers is: VNX_MAX_SIZE = 0xFFFFFFFF elements
 * - The maximum combined size of all primitive fields (including static arrays of integral type) inside a struct or class is: VNX_BUFFER_SIZE = 16384 bytes
 * 
 */







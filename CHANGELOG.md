## [v1.9.2]

- Variant null copy fix
- added Terminal dmesg command
- added vnx::shutdown_host()
- added JRPC_Client
- added Process self_test_all()
- extended is_equivalent() to cover std::pair, std::tuple, std::array and structs
- forced enum_t to be 32-bit
- added std::tuple support (tuple<> in VNI)
- added Frame + Stream
- added VNX_TYPE_ID
- using switch() when possible instead of std::dynamic_pointer_cast()
- pair and tuple are now always serialized as "extended" fields for backwards compatibility

## [v1.9.1]

- Publishers send FlowMessages now
- vnx::get_all_modules() refactor
- Proxy send_buffer_size default 128 kB (to limit latency)
- added vnx_task_priority, vnx_default_queue_ms, vnx_default_queue_size
- Variant read support for CODE_STRUCT
- improved command line parsing
- vnx::read_type_code() returns value now
- added CODE_OPTIONAL
- added nullptr_t functions
- added vnx::optional
- added CPU load stats
- added load stats command to terminal
- added SocketInputStream
- added 'priority' config to set process priority
- vnxservice default node localhost:4444

## [v1.9.0]

- added Module default pipe on module id
- added vnx_self_test() to ModuleInterface
- Visitor refactor
- RPC calls are now backwards compatible with type name changes
- added ToObject visitor
- Variant comparison fixes
- added Value get/set_field_by_index() + is_void()
- added Tuple
- Clients now support Generic return values
- added Proxy wait_on_disconnect()
- added JRPC_Proxy
- VNI Module inheritance support
- added Pipe mode PIPE_MODE_LATEST
- config array append feature (name+)
- added vnx::istream + vnx::ostream
- JSON parsing overhaul (new api)

## [v1.8.2]

- added Proxy wait_on_connect()
- Proxy block_until_connect + block_until_reconnect
- added login option to tools
- added vnx::to_string_value_full() for enums
- enums are type safe now
- Proxy + Server default_access for anonymous clients
- added vnxpasswd tool
- Proxy missing socket close fix
- added Process reload_config()
- renamed configs vnx_server_map -> vnx.server_map (backwards compatible)
- added config protection
- Hash64::rand() returns non-zero value
- session handling
- Terminal fix to avoid std::terminate on shutdown
- Proxy allow NON_BLOCKING for Sample and Return, ignore overflow
- added authentication
- added ModuleInterface vnx_get_module_info()
- added Handle get_id() get_name()
- added VNI Annotation + TypeCode permission
- split Module into ModuleBase and Module
- added Handle is_running()
- accept fix for CODE_OBJECT
- write_dynamic() fix for CODE_NULL
- Object publish support
- added Message RESEND feature
- added request_t
- added vnx_read_fallback(const Variant&)

## [v1.8.1]

- added vnx_shutdown(), changed shutdown procedure
- Node::notify() fix for nullptr
- proper Object get_type_name() and get_type_code()
- added TypeCode::get_method_name()
- get_type_name() returns std::string now
- removed obsolete Variant is_list() and is_value()
- added Module vnx_auto_shutdown
- only exact topic matches for Terminal commands
- write_to_file() for windows
- added nullptr support + dynamic null support
- added VNI list

## [v1.8.0]

- AsyncClient refactor
- std::shared_ptr function arguments now by value
- added optional Pipe priority
- added TypeCode::get_field_type_code()
- read_array() and read_vector() now compatible with CODE_MATRIX
- added from_string_value()
- Variant::is_array() true also for CODE_MATRIX
- Terminal auto-completion
- Terminal module command
- added VNI set
- Variant from_string_value() fixes
- Object::as_value() fix

## [v1.7.3]

- TypeCode::accept() fixes
- added more ModuleInterface functions
- added Module registry (vnx::get_module(), etc)
- Client, AsyncClient, GenericClient and GenericAsyncClients are thread-safe now
- Terminal auto-completion
- Terminal colors
- Pipe cleanup and fixes
- added Buffer::read_file()
- AsyncClient fixes
- added Router::forward_map
- added special topic name "null" which means no topic (TopicPtr = nullptr)
- set_config() now supports setting multiple values via an Object as value (key = namespace)
- Values are now dynamically written as Objects (CODE_OBJECT)

## [v1.7.2]

- added Value get_field() / set_field()

## [v1.7.1]

- added CODE_BOOL (not forwards compatible)

## [v1.7.0]

- added CODE_STRING (not forwards compatible)

## [v1.6.0]

- vnxdump do longer does regex matching, will only dump specified topics
- dump command in terminal also no longer does regex matching, same as vnxdump

## [v1.5.0]

- removed ambiguous subscribe/unsubscribe functions in vnx::Subscriber
- codegen fix for segfault in case of reading an un-matched nested type (only possible when using vnx_type_map)
- istream read fix for vnx::Object, previously did not clear the object first
- added Variant::to_object()
- Recorder publishes RecorderStatus now
- write_to_file() ignores empty file name now
- added Module::get_vnx_node()

## [v1.4.3]

- added "vnx_type_map" config option to vnx::init()
- added "vnx_server_map" and "vnx_proxy_map" config options to vnx::init()
- replaced "void from_string(const std::string& str, std::map<std::string, std::string>& value)" with "bool read_object(const std::string& str, std::map<std::string, std::string>& object)"
- added "const TypeCode* get_type_code(const std::string& type_name)"

## [v1.4.2]

- vnxcppcodegen fix for missing inter-package dependency includes in package.hxx

## [v1.4.1]

- Fix for command line parsing of arrays, only worked for first parameter before
- Added write_dynamic() support for custom comparator std::set, std::unordered_set, std::map and std::unordered_map

## [v1.4.0]

- vnxread fix for -t option, now resolves actual type name
- SpyTool, vnxdump fix for null value
- SpyTool, vnxdump fix for not picking up new topics during run-time
- Using Hash128 as key for Module::seq_map instead of Hash64, collisions should no longer be a concern
- Removed obsolete Module::exit() function
- Made Hash64 + Hash128 to_string() and to_hex_string() functions const, as they should be
- Added Module::vnx_virtual_time option to better control if a Module should use virtual time or not
- *_async() request functions no longer throw exceptions, as they should not
- Added vnxgraph tool

## [v1.3.4]

- Added Variant::get_empty()
- Changed "Variant::operator[](const std::string& name) const" to return a reference, instead of a copy

## [v1.3.3]

- Added vnxplay + vnxrecord to vnx-base

## [v1.3.2]

- Added vnx::create(const std::string& type_name)
- vnx::read_object() fix

## [v1.3.1]

- Added "operator Variant::char() const"
- Added dedicated shutdown monitor thread to avoid dead-locks in case of forced shutdown
- vnxclose now returns 0 in case target process does not exist, previously tried to connect indefinitely
- Added vnxtopic tool


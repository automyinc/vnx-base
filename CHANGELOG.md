
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


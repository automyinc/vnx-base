
## [v1.4.2]

- vnxcppcodegen fix for missing inter-package dependency includes in package.hxx

## [v1.4.1]

- Fix for command line parsing of array arguments
- Added dynamic read/write support for custom comparison templates of std::set, std::unordered_set, std::map and std::unorderd_map

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
- Fix for command line parsing of arrays, only worked for first parameter before
- Addded write_dynamic() support for custom comparator std::set, std::unordered_set, std::map and std::unordered_map

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


cmake_minimum_required(VERSION 2.6)
project(vnx-base)

get_property(LIB64 GLOBAL PROPERTY FIND_LIBRARY_USE_LIB64_PATHS)

if("${LIB64}" STREQUAL "TRUE")
    set(LIBSUFFIX 64)
else()
    set(LIBSUFFIX "")
endif()

install(DIRECTORY
	generated/include/vnx
	include/vnx
	DESTINATION include
)

install(DIRECTORY
	interface/vnx
	DESTINATION interface
)

install(PROGRAMS
	lib/libvnx_base.so
	DESTINATION lib${LIBSUFFIX}
)

install(PROGRAMS
	bin/vnxrouter
	bin/vnxclose
	bin/vnxdump
	bin/vnxread
	bin/vnxtimeserver
	bin/vnxtopic
	bin/vnxrecord
	bin/vnxplay
	bin/vnxgraph
	DESTINATION bin
)


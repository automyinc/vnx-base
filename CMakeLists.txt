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
	${ARCH}/${DIST}/lib/libvnx_base.so
	DESTINATION lib${LIBSUFFIX}
)

install(PROGRAMS
	${ARCH}/${DIST}/bin/vnxrouter
	${ARCH}/${DIST}/bin/vnxclose
	${ARCH}/${DIST}/bin/vnxdump
	${ARCH}/${DIST}/bin/vnxread
	${ARCH}/${DIST}/bin/vnxtimeserver
	DESTINATION bin
)


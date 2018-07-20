cmake_minimum_required(VERSION 2.6)
project(vnx-base)

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
	${ARCH}/lib/libvnx_base.so
	DESTINATION lib
)

install(PROGRAMS
	${ARCH}/bin/vnxrouter
	${ARCH}/bin/vnxclose
	${ARCH}/bin/vnxdump
	${ARCH}/bin/vnxread
	${ARCH}/bin/vnxtimeserver
	DESTINATION bin
)


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
	${ARCH}/${DIST}/lib/libvnx_base.so
	DESTINATION lib
)

install(PROGRAMS
	${ARCH}/${DIST}/bin/vnxrouter
	${ARCH}/${DIST}/bin/vnxclose
	${ARCH}/${DIST}/bin/vnxdump
	${ARCH}/${DIST}/bin/vnxread
	${ARCH}/${DIST}/bin/vnxtimeserver
	DESTINATION bin
)


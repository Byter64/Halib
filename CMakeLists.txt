cmake_minimum_required(VERSION 4.0)

#If you want to build for desktop, use the flag -DDESKTOPBUILD, when running cmake
option(DESKTOPBUILD "Replaces the Hall library with Hall_Desktop. Hall_Desktop is for Desktop builds.")


project("Halib")

include(FetchContent)
FetchContent_Declare(Hall
	GIT_REPOSITORY https://github.com/byter64/Hall.git
	GIT_TAG main
)
FetchContent_MakeAvailable(Hall)

set(SOURCES
	#Add the .cpp files here
	"Filesystem.cpp"
)


if(DESKTOPBUILD)
	#This library contains the desktop implementation of Halib
	add_library(Halib_Desktop STATIC
		${SOURCES}
	)

	target_link_libraries(Halib_Desktop
		Hall
	)

	target_include_directories(Halib_Desktop
		PUBLIC SYSTEM include
	)
else()

	#This library cointains the bare metal implementation of Halib for wueHans
	#In order to build this target without the Softwaretemplate, you need to add and use another toolchain (see softwaretemplate/cmake and softwaretemplate/CMakeLists.txt)
	add_library(Halib STATIC
		${SOURCES}
	)

	target_compile_options(Halib
		PUBLIC -fno-exceptions
		PUBLIC -nostdlib
		PUBLIC -fno-unwind-tables
		PUBLIC -fno-rtti
		PUBLIC -march=rv32im
		PUBLIC -Os
		PUBLIC -ffreestanding
		PUBLIC -Bstatic
		PUBLIC -nostdinc
	)

	target_link_options(Halib
	  	PUBLIC -nostdlib
	  	PUBLIC -Wl,--gc-sections
	  	PUBLIC -ffreestanding
	  	PUBLIC -Bstatic
	  	PUBLIC -nostdlib
	)

	target_include_directories(Halib
	  	PUBLIC SYSTEM include
	)	
endif()

cmake_minimum_required(VERSION 4.0)

#If you want to build for desktop, use the flag -DDESKTOPBUILD, when running cmake
option(DESKTOPBUILD "Replaces the Hall library with Hall_Desktop. Hall_Desktop is for Desktop builds.")

set(CMAKE_CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED ON)

project("Halib")

include(FetchContent)
FetchContent_Declare(Hall
	GIT_REPOSITORY "https://github.com/Byter64/Hall"
	GIT_TAG main
)
FetchContent_MakeAvailable(Hall)

#FetchContent_Declare(freetype
#URL https://download.savannah.gnu.org/releases/freetype/freetype-2.13.3.tar.gz
#)
#FetchContent_MakeAvailable(freetype)

FetchContent_Declare(glm
	GIT_REPOSITORY https://github.com/g-truc/glm
)
FetchContent_MakeAvailable(glm)

set(SOURCES
	#Add the .c/.cpp files here
	"external/libbmpread/libbmpread/bmpread.c"
	"source/Graphic/Image.cpp"
	"source/Graphic/Color.cpp"
	#"source/Graphic/Font.cpp"
	"source/System.cpp"
	"source/Graphic/Render.cpp"
	"source/Graphic/Sprite.cpp"
	"source/Entity.cpp"
	"source/Graphic/Rendersystem.cpp"
	"source/Entitysystem.cpp"
	"external/wav_reader/lib/wav_reader_methods.cpp"
	"source/Audio/Audio.cpp"
	"source/Audio/Audiosystem.cpp"
	"source/Graphic/Rect.cpp"
)

set(INCLUDE_DIRS
	PRIVATE "external/libbmpread/libbmpread/include"
	PRIVATE "external/wav_reader/lib"
)

set(LINK_LIBS
	#freetype
	glm::glm
	
)


if(DESKTOPBUILD)
	#This library contains the desktop implementation of Halib
	add_library(Halib_Desktop STATIC
		${SOURCES}
	)

	target_link_libraries(Halib_Desktop
		Hall_Desktop
		${LINK_LIBS}
	)

	target_include_directories(Halib_Desktop
		PUBLIC "include"
		${INCLUDE_DIRS}
	)

	target_compile_definitions(Halib_Desktop PRIVATE DESKTOP)
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

	target_link_libraries(Halib
		Hall
		${LINK_LIBS}
	)

	target_include_directories(Halib
		PUBLIC "include"
		${INCLUDE_DIRS}
	)

	target_compile_definitions(Halib PRIVATE WUEHANS)
endif()

find_path(SDL2_INCLUDE_DIR SDL.h
	HINTS $ENV{SDL2_ROOT}
	PATH_SUFFIXES include/SDL2 include
	PATHS "/Library/Frameworks"
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(PATH_SUFFIXES lib64 lib/x64 lib)
else()
	set(PATH_SUFFIXES lib/x86 lib)
endif()

find_library(SDL2_LIBRARY
	NAMES SDL2
	HINTS $ENV{SDL2_ROOT}
	PATH_SUFFIXES ${PATH_SUFFIXES}
	PATHS "/Library/Frameworks"
)

set(SDL2_LIBRARY "${SDL2_LIBRARY} -framework Cocoa" CACHE STRING "Where the SDL2 Library can be found")


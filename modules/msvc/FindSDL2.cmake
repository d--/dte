set(SDL2_PATH "$ENV{SDL2_ROOT}" CACHE PATH "Path to extracted SDL2-devel zip")

set(SDL2_ROOT_DIR "${SDL2_PATH}")
set(SDL2_INCLUDE_DIR "${SDL2_PATH}/include")

if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIB_DIR "${SDL2_PATH}/lib/x64")
else ()
    set(SDL2_LIB_DIR "${SDL2_PATH}/lib/x86")
endif ()

set(SDL2_LIBRARIES "${SDL2_LIB_DIR}/SDL2.lib;${SDL2_LIB_DIR}/SDL2main.lib")
string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
set(SDL2_TTF_PATH "$ENV{SDL2_TTF_ROOT}"
    CACHE PATH "Path to extracted SDL2_ttf")

set(SDL2_TTF_ROOT_DIR "${SDL2_TTF_PATH}")
set(SDL2_TTF_INCLUDE_DIR "${SDL2_TTF_PATH}/include")

if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_TTF_LIB_DIR "${SDL2_TTF_PATH}/lib/x64")
else ()
    set(SDL2_TTF_LIB_DIR "${SDL2_TTF_PATH}/lib/x86")
endif ()

set(SDL2_TTF_LIBRARY "${SDL2_TTF_LIB_DIR}/SDL2_ttf.lib")
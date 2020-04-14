add_executable(tetris tetris.cpp)

if (MSVC)
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules/msvc")
endif ()

if (APPLE)
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules/apple")
endif ()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

target_include_directories(tetris PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/src/game"
    "${SDL2_INCLUDE_DIR}"
    "${SDL2_IMAGE_INCLUDE_DIR}")

target_link_libraries(tetris PUBLIC
    game
    "${SDL2_LIBRARIES}"
    "${SDL2_IMAGE_LIBRARY}")

if (MSVC)
    add_custom_command(TARGET tetris POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${SDL2_LIB_DIR}/SDL2.dll"
        "${SDL2_IMAGE_LIB_DIR}/libjpeg-9.dll"
        "${SDL2_IMAGE_LIB_DIR}/libpng16-16.dll"
        "${SDL2_IMAGE_LIB_DIR}/libtiff-5.dll"
        "${SDL2_IMAGE_LIB_DIR}/libwebp-7.dll"
        "${SDL2_IMAGE_LIB_DIR}/zlib1.dll"
        "${SDL2_IMAGE_LIB_DIR}/SDL2_image.dll"
        $<TARGET_FILE_DIR:tetris>)
endif (MSVC)


add_executable(tetris tetris.cpp)

if (MSVC)
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules/msvc")
endif ()

if (APPLE)
    set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules/apple")
endif ()

find_package(SDL2 REQUIRED)

target_include_directories(tetris PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${SDL2_INCLUDE_DIR}")

target_link_libraries(tetris PUBLIC
    "${SDL2_LIBRARIES}")

if (MSVC)
    add_custom_command(TARGET tetris POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${SDL2_LIB_DIR}/SDL2.dll"
        $<TARGET_FILE_DIR:tetris>)
endif (MSVC)


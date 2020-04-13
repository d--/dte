add_executable(tetris tetris.cpp)

if(APPLE)
    find_package(SDL2 REQUIRED)
endif(APPLE)

target_include_directories(tetris PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/ds"
    "${SDL2_INCLUDE_DIRS}")

target_link_libraries(tetris PUBLIC
    "${SDL2_LIBRARIES}")
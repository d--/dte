add_library(game
        asset/asset_manager.cpp
        asset/texture_store.cpp
        component/draw.h
        component/input.h
        component/transform.h
        core/entity.cpp
        entities/first/block_input.cpp
        entities/first/block_transform.cpp
        entities/first/block_draw.cpp
        gamestates/generic_loading.cpp
        gamestates/sandbox_state.cpp
        gamestates/state_manager.cpp
        job/asset_job.h
        job/asset_job_batch.cpp
        job/image_load_job.cpp
        job/text_load_job.cpp
        job/texture_job.cpp)

target_include_directories(game PUBLIC
        "${SDL2_IMAGE_INCLUDE_DIR}"
        "${SDL2_TTF_INCLUDE_DIR}")

add_executable(tetris game.cpp)

target_include_directories(tetris PUBLIC
        "${PROJECT_BINARY_DIR}"
        "${PROJECT_SOURCE_DIR}/src"
        "${SDL2_IMAGE_INCLUDE_DIR}"
        "${SDL2_TTF_INCLUDE_DIR}")

target_link_libraries(tetris PUBLIC
        game
        "${SDL2_LIBRARY}"
        "${SDL2_IMAGE_LIBRARY}"
        "${SDL2_TTF_LIBRARY}")

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
            "${SDL2_TTF_LIB_DIR}/libfreetype-6.dll"
            "${SDL2_TTF_LIB_DIR}/SDL2_ttf.dll"
            $<TARGET_FILE_DIR:tetris>)
endif (MSVC)

file(COPY "${DTE_ASSET_PATH}" DESTINATION "${CMAKE_BINARY_DIR}")
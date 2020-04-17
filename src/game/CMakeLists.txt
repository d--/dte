add_library(game
    actor.cpp
    texture.cpp
    asset_manager.cpp
    gamestates/gamestate.cpp
    gamestates/gameload.cpp)

target_include_directories(game PUBLIC
    "${SDL2_INCLUDE_DIR}"
    "${SDL2_IMAGE_INCLUDE_DIR}")

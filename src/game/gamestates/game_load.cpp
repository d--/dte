#include "game_load.h"
#include <iostream>

namespace dte {
    GameLoad::GameLoad(AssetManager *am) :
        assetManager(am) {}

    void GameLoad::update() {
        if (assetManager->isLoadDone()) {
            std::cout << "load is done" << std::endl;
        } else {
            std::cout << "loading..." << std::endl;
        }
    }
}

#include "game_load.h"
#include <iostream>

#include "../asset/asset_manager.h"

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

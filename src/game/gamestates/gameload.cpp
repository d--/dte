#include "gameload.h"
#include <iostream>

namespace dte {
    GameLoad::GameLoad(AssetManager *am) :
        assetManager(am) {}

    GameLoad::~GameLoad() {}

    void GameLoad::update() {
        if (assetManager->isLoadDone()) {
            std::cout << "load is done" << std::endl;
        } else {
            std::cout << "loading..." << std::endl;
        }
    }
}

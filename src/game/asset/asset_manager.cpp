#include <SDL.h>
#include <SDL_image.h>
#include "asset_manager.h"
#include "assets.h"

namespace dte {
    AssetManager::AssetManager() :
        loadDone(false),
        errorFlag(false),
        error("") {}

    void AssetManager::loadImages() {
        // So... this should load SDL_Surfaces which should be shuffled into   
        // the main thread (loading state?  something special?) via a queue to 
        // then be converted to SDL_Textures where the OpenGL context lives.

        // I'll need to spin up an SDL_Thread, since std::thread isn't 
        // available on MacOS and I should be doing something more platform 
        // agnostic anyway.  (More platform agnostic than relying on the C++ 
        // compiler... I guess...?)

        std::thread textureLoadThread = std::thread([=]() {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            setLoadDone(true);
        });
        textureLoadThread.detach();
    }

    bool AssetManager::isLoadDone() {
        bool done;
        loadDoneMutex.lock();
        done = loadDone;
        loadDoneMutex.unlock();
        return done;
    }

    void AssetManager::setLoadDone(bool done) {
        loadDoneMutex.lock();
        loadDone = done;
        loadDoneMutex.unlock();
    }

    AssetManager::~AssetManager() {}

    std::string AssetManager::getError() {
        return error;
    }
}
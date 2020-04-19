#include <SDL_image.h>
#include "asset_manager.h"
#include "assets.h"

namespace dte {
    AssetManager::AssetManager() :
        loadDone(false),
        errorFlag(false),
        error("") {}

    SDL_Surface * AssetManager::loadImage(std::string path) {
        SDL_Surface *surface = IMG_Load(path.c_str());
        if (surface == nullptr) {
            SDL_Log("Could not load image: %s\n", path.c_str());
            SDL_Log("Error: %s\n", IMG_GetError());
            return nullptr;
        }
        return surface;
    }

    void AssetManager::loadImages() {
        // So... this should load SDL_Surfaces which should be shuffled into   
        // the main thread (loading state?  something special?) via a queue to 
        // then be converted to SDL_Textures where the OpenGL context lives.

        SDL_Thread *loadThread;
        loadThread = SDL_CreateThread(loadThreadFn,
            "DTEImageLoadThread", (void *) this);
        SDL_DetachThread(loadThread);
    }

    int AssetManager::loadThreadFn(void *ptr) {
        AssetManager *manager = (AssetManager *) ptr;
        SDL_Delay(5000);
        manager->setLoadDone(true);
        return 0;
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

    std::string AssetManager::getError() {
        return error;
    }
}
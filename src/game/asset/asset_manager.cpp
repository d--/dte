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
        SDL_Thread *loadThread;
        loadThread = SDL_CreateThread(loadImagesThreadFn,
            "DTEImageLoadThread", (void *) this);
        SDL_DetachThread(loadThread);
    }

    int AssetManager::loadImagesThreadFn(void *ptr) {
        AssetManager *manager = (AssetManager *) ptr;
        for (struct asset_image image : assetImages) {
            SDL_Surface *surface = loadImage(image.location);
            TextureJob job(image.location, surface);
            manager->textureJobQueueMutex.lock();
            manager->textureJobQueue.push_back(job);
            manager->textureJobQueueMutex.unlock();
        }

        // todo: remove this; just here for simulation
        SDL_Delay(5000);
        manager->setLoadDone(true);
        return 0;
    }

    bool AssetManager::isLoadDone() {
        std::shared_lock lock(loadDoneMutex);
        return loadDone;
    }

    void AssetManager::setLoadDone(bool done) {
        std::unique_lock lock(loadDoneMutex);
        loadDone = done;
    }

    std::string AssetManager::getError() {
        return error;
    }

    bool AssetManager::hasNewTextureJobs() {
        std::shared_lock lock(textureJobQueueMutex);
        return !(textureJobQueue.empty());
    }

    TextureJob AssetManager::getNextTextureJob() {
        std::unique_lock lock(textureJobQueueMutex);
        TextureJob job = textureJobQueue.front();
        textureJobQueue.pop_front();
        return job;
    }
}
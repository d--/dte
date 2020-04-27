#include <SDL_image.h>
#include "asset_manager.h"
#include "assets.h"

namespace dte {
    AssetManager::AssetManager() :
        loadDone(false),
        errorFlag(false),
        error("") {}

    void AssetManager::loadAllImages() {
        for (const struct asset_image& image : assetImages) {
            loadTextureJob(this, image);
        }
        loadDone = true;
    }

    void AssetManager::loadImagesAsync() {
        SDL_Thread *loadThread;
        loadThread = SDL_CreateThread(loadImagesThreadFn,
            "DTEImageLoadThread", (void *) this);
        SDL_DetachThread(loadThread);
    }

    int AssetManager::loadImagesThreadFn(void *ptr) {
        auto *manager = (AssetManager *) ptr;
        for (const struct asset_image& image : assetImages) {
            // todo: remove this; just here for simulation
            SDL_Delay(1000);

            loadTextureJob(manager, image);
        }

        manager->setLoadDone(true);
        return 0;
    }

    void AssetManager::loadTextureJob(AssetManager *manager,
            const struct asset_image& image) {
        std::string basePath(SDL_GetBasePath());
        std::string location(basePath + image.location);
        SDL_Surface *surface = IMG_Load(location.c_str());
        if (surface == nullptr) {
            SDL_Log("Could not load image: %s\n", image.location.c_str());
            SDL_Log("Error: %s\n", IMG_GetError());
            return;
        }

        TextureJob job(image.id, surface);
        std::unique_lock lock(manager->textureJobQueueMutex);
        manager->textureJobQueue.push_back(job);
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
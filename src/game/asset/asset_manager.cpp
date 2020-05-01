#include <SDL_image.h>
#include "asset_manager.h"

namespace dte {
    AssetManager::AssetManager() : quit(false) {
        workThread = SDL_CreateThread(workThreadFn,
                "DTEImageLoadThread", (void *) this);
    }

    AssetManager::~AssetManager() {
        quit = true;
        int threadReturn = 0;
        SDL_WaitThread(workThread, &threadReturn);
        if (threadReturn < 0) {
            SDL_Log("Asset manager shutdown failed: %s", SDL_GetError());
        }
    }

    bool AssetManager::isQuit() const {
        return quit;
    }

    int AssetManager::workThreadFn(void *ptr) {
        auto manager = (AssetManager *) ptr;
        int variableDelay = 2;
        int delayMax = 500;
        while (!manager->isQuit()) {
            if (manager->hasBatches()) {
                AssetJobBatch *batch = manager->getNextBatch();
                batch->execute(manager);
                variableDelay = 2;
            } else {
                SDL_Delay(variableDelay);
                if (variableDelay < delayMax) {
                    variableDelay *= 2;
                }
            }
        }
        return 0;
    }

    // main thread only
    void AssetManager::pumpTextures(SDL_Renderer *renderer) {
        while (hasTextureJobs()) {
            getNextTextureJob()->execute(renderer, textureStore);
        }
    }

    bool AssetManager::hasBatches() {
        std::shared_lock lock(batchQueueMutex);
        return !(batchQueue.empty());
    }

    AssetJobBatch *AssetManager::getNextBatch() {
        std::unique_lock lock(batchQueueMutex);
        AssetJobBatch *batch = batchQueue.front();
        batchQueue.pop_front();
        return batch;
    }

    bool AssetManager::hasTextureJobs() {
        std::shared_lock lock(textureJobQueueMutex);
        return !(textureJobQueue.empty());
    }

    TextureJob *AssetManager::getNextTextureJob() {
        std::unique_lock lock(textureJobQueueMutex);
        TextureJob *job = textureJobQueue.front();
        textureJobQueue.pop_front();
        return job;
    }

    SDL_Texture *AssetManager::getTexture(const std::string& id) {
        return textureStore.getTexture(id);
    }

    void AssetManager::executeTextureJobAsync(TextureJob *job) {
        std::unique_lock lock(textureJobQueueMutex);
        textureJobQueue.push_back(job);
    }

    void AssetManager::executeTextureJob(TextureJob *job) {
        this->executeTextureJobAsync(job);
        Uint32 variableDelay = 2;
        Uint32 delayMax = 200;
        while (!job->isFinished()) {
            SDL_Delay(variableDelay);
            if (variableDelay < delayMax) {
                variableDelay *= 2;
            }
        }
    }

    void AssetManager::processBatch(AssetJobBatch *batch) {
        std::unique_lock lock(batchQueueMutex);
        batchQueue.push_back(batch);
    }
}
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
            if (manager->hasJobs()) {
                AssetJob *job = manager->getNextJob();
                job->execute(manager);
                delete job;
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
            TextureJob *job = getNextTextureJob();
            SDL_Texture *texture = job->convertSurface(renderer);
            std::string id = job->getImageID();
            delete job;
            textures.insert(std::make_pair(id, texture));
        }
    }

    void AssetManager::enqueueJob(TextureJob *job) {
        std::unique_lock lock(textureJobQueueMutex);
        textureJobQueue.push_back(job);
    }

    void AssetManager::enqueueJob(AssetJob *job) {
        std::unique_lock lock(jobQueueMutex);
        jobQueue.push_back(job);
    }

    bool AssetManager::hasJobs() {
        std::shared_lock lock(jobQueueMutex);
        return !(jobQueue.empty());
    }

    AssetJob *AssetManager::getNextJob() {
        std::unique_lock lock(jobQueueMutex);
        AssetJob *job = jobQueue.front();
        jobQueue.pop_front();
        return job;
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

    bool AssetManager::jobQueuesEmpty() {
        return !(hasJobs() || hasTextureJobs());
    }

    SDL_Texture *AssetManager::getTexture(const std::string& id) {
        return textures.at(id);
    }
}
#pragma once

#include <SDL.h>
#include <deque>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include "../job/asset_job.h"
#include "../job/texture_job.h"
#include "../job/asset_job_batch.h"
#include "texture_store.h"

namespace dte {
    class AssetJob;
    class AssetJobBatch;
    class AssetManager {
    public:
        AssetManager();
        ~AssetManager();
        bool isQuit() const;
        void pumpTextures(SDL_Renderer *renderer);
        void processBatch(AssetJobBatch *batch);
        SDL_Texture *getTexture(const std::string& id);
        void submitTextureJob(TextureJob *job);
    private:
        SDL_Thread *workThread;
        static int workThreadFn(void *ptr);
        bool quit;

        std::deque<AssetJobBatch *> batchQueue;
        std::shared_timed_mutex batchQueueMutex;
        bool hasBatches();
        AssetJobBatch *getNextBatch();

        std::deque<TextureJob *> textureJobQueue;
        std::shared_timed_mutex textureJobQueueMutex;
        bool hasTextureJobs();
        TextureJob *getNextTextureJob();

        TextureStore textureStore;
    };
}
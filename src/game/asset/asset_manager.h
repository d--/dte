#pragma once

#include <SDL.h>
#include <deque>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include "../job/asset_job.h"
#include "../job/texture.h"

namespace dte {
    class AssetJob;
    class AssetManager {
    public:
        AssetManager();
        ~AssetManager();
        bool isQuit() const;
        void pumpTextures(SDL_Renderer *renderer);
        void enqueueJob(TextureJob *job);
        void enqueueJob(AssetJob *job);

        SDL_Texture *getTexture(const std::string& id);
        bool hasTexture(const std::string &id);
    private:
        SDL_Thread *workThread;
        static int workThreadFn(void *ptr);
        bool quit;

        std::deque<AssetJob *> jobQueue;
        std::shared_timed_mutex jobQueueMutex;
        std::deque<TextureJob *> textureJobQueue;
        std::shared_timed_mutex textureJobQueueMutex;
        bool hasJobs();
        bool hasTextureJobs();
        AssetJob *getNextJob();
        TextureJob *getNextTextureJob();

        std::unordered_map<std::string, SDL_Texture *> textures;
    };
}
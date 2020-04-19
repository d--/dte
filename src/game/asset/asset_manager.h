#pragma once

#include <SDL.h>
#include <deque>
#include <vector>
#include <mutex>
#include <string>
#include "texture_job.h"

namespace dte {
    class AssetManager {
        public:
            AssetManager();
            void loadImages();
            bool isLoadDone();
            std::string getError();
            bool hasNewTextureJobs();
            TextureJob getNextTextureJob();
        private:
            std::deque<TextureJob> textureJobQueue;
            std::mutex textureJobQueueMutex;
            static SDL_Surface * loadImage(std::string path);
            static int loadThreadFn(void *ptr);
            bool loadDone;
            void setLoadDone(bool done);
            std::mutex loadDoneMutex;
            bool errorFlag;
            std::string error;
    };
}
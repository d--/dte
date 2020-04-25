#pragma once

#include <SDL.h>
#include <deque>
#include <vector>
#include <mutex>
#include <shared_mutex>
#include <string>
#include "../job/texture.h"

namespace dte {
    class AssetManager {
        public:
            AssetManager();
            // todo: temporary for entity component separation testing until it 
            // makes sense to do things asynchronously
            void loadAllImages();
            void loadImagesAsync();
            bool isLoadDone();
            std::string getError();
            bool hasNewTextureJobs();
            TextureJob getNextTextureJob();
        private:
            std::deque<TextureJob> textureJobQueue;
            std::shared_timed_mutex textureJobQueueMutex;
            static void loadTextureJob(AssetManager *manager,
                struct asset_image image);
            static int loadImagesThreadFn(void *ptr);
            bool loadDone;
            void setLoadDone(bool done);
            std::shared_timed_mutex loadDoneMutex;
            bool errorFlag;
            std::string error;
    };
}
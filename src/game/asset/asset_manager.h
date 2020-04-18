#pragma once

#include <SDL.h>
#include <vector>
#include <mutex>
#include <string>

namespace dte {
    class AssetManager {
        public:
            AssetManager();
            ~AssetManager();
            void loadImages();
            bool isLoadDone();
            std::string getError();
        private:
            SDL_Texture* loadImage(std::string path);
            static int loadThreadFn(void *ptr);
            bool loadDone;
            void setLoadDone(bool done);
            std::mutex loadDoneMutex;
            bool errorFlag;
            std::string error;
    };
}
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
            void setLoadDone(bool done);
            std::string getError();
        private:
            SDL_Texture* loadImage(std::string path);
            bool loadDone;
            std::mutex loadDoneMutex;
            bool errorFlag;
            std::string error;
    };
}
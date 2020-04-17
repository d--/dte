#pragma once

#include <SDL.h>
#include <vector>
#include <mutex>
#include <string>
#include "texture.h"

namespace dte {
    class AssetManager {
        public:
            AssetManager(SDL_Renderer *renderer);
            void loadTextures();
            bool isLoadDone();
            ~AssetManager();
            std::string getError();
        private:
            SDL_Renderer *renderer;
            SDL_Texture* loadTexture(std::string path);
            bool loadDoneFlag;
            std::mutex loadDoneFlagMutex;
            bool errorFlag;
            std::string error;
            std::vector<Texture> textures;
    };
}
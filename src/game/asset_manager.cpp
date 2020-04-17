#include "asset_manager.h"
#include "assets.h"
#include <SDL.h>
#include <SDL_image.h>

namespace dte {
    AssetManager::AssetManager(SDL_Renderer *renderer) :
        textures(std::vector<Texture>()),
        loadDoneFlag(false),
        errorFlag(false),
        error("") {}

    void AssetManager::loadTextures() {
        std::thread textureLoadThread = std::thread([=]() {
            // todo: This will not work.  Renderer is main-thread only.

            // for (struct asset_texture t : assetTextures) {
            //     SDL_Texture *sdlTexture = loadTexture(t.location);
            //     if (sdlTexture == nullptr) {
            //         error = "Unable to load texture: " + t.location;
            //         errorFlag = true;
            //         return;
            //     }
            //     textures.push_back(Texture(sdlTexture));
            // }

            // loadDoneFlagMutex.lock();
            // loadDoneFlag = true;
            // loadDoneFlagMutex.unlock();

            std::this_thread::sleep_for(std::chrono::seconds(5));
            loadDoneFlagMutex.lock();
            loadDoneFlag = true;
            loadDoneFlagMutex.unlock();
        });
        textureLoadThread.detach();
    }

    bool AssetManager::isLoadDone() {
        bool loadDone;
        loadDoneFlagMutex.lock();
        loadDone = loadDoneFlag;
        loadDoneFlagMutex.unlock();
        return loadDone;
    }

    AssetManager::~AssetManager() {}

    std::string AssetManager::getError() {
        return error;
    }

    SDL_Texture* AssetManager::loadTexture(std::string path) {
        SDL_Texture* texture;

        SDL_Surface* surface = IMG_Load(path.c_str());
        if (surface == nullptr)
        {
            SDL_Log("Could not load image: %s\n", path.c_str());
            SDL_Log("Error: %s\n", IMG_GetError());
            return nullptr;
        }

        texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == nullptr)
        {
            SDL_Log("Could not create texture: %s\n", path.c_str());
            SDL_Log("Error: %s\n", SDL_GetError());
        }

        SDL_FreeSurface(surface);
        return texture;
    }
}
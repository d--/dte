#pragma once

#include <unordered_map>
#include <string>
#include <SDL.h>

namespace dte {
    class TextureStore {
    public:
        SDL_Texture *getTexture(const std::string& id);
        void insert(const std::string& id, SDL_Texture *texture);
    private:
        std::unordered_map<std::string, SDL_Texture *> textures;
    };
}

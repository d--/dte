#include "texture_store.h"

namespace dte {
    SDL_Texture *TextureStore::getTexture(const std::string &id) {
        return textures.at(id);
    }

    void TextureStore::insert(const std::string &id, SDL_Texture *texture) {
        textures.insert(std::make_pair(id, texture));
    }
}
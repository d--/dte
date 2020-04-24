#include "texture.h"

namespace dte {
    TextureJob::TextureJob(std::string id, SDL_Surface *surface) :
        imageId(id),
        sdlSurface(surface) {}

    std::string TextureJob::getImageID() {
        return imageId;
    }

    SDL_Texture * TextureJob::convertSurface(SDL_Renderer *renderer) {
        SDL_Texture* texture;
        texture = SDL_CreateTextureFromSurface(renderer, sdlSurface);
        if (texture == nullptr) {
            SDL_Log("Could not create texture: %s\n", imageId.c_str());
            SDL_Log("Error: %s\n", SDL_GetError());
        }

        SDL_FreeSurface(sdlSurface);
        return texture;
    }
}
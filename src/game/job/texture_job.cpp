#include "texture_job.h"

#include <utility>

namespace dte {
    TextureJob::TextureJob(std::string id, SDL_Surface *surface) :
        imageId(std::move(id)),
        sdlSurface(surface) {}

    void TextureJob::execute(SDL_Renderer *renderer, TextureStore *store) {
        SDL_Texture* texture;
        texture = SDL_CreateTextureFromSurface(renderer, sdlSurface);
        if (texture == nullptr) {
            SDL_Log("Could not create texture: %s\n", imageId.c_str());
            SDL_Log("Error: %s\n", SDL_GetError());
        }

        SDL_FreeSurface(sdlSurface);
        store->insert(imageId, texture);

        std::unique_lock lock(finishedMutex);
        finished = true;
    }

    bool TextureJob::isFinished() {
        std::shared_lock lock(finishedMutex);
        return finished;
    }
}

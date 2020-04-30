#pragma once

#include <SDL.h>
#include <string>
#include <shared_mutex>
#include "../asset/texture_store.h"

namespace dte {
    class TextureJob {
        public:
            TextureJob(std::string id, SDL_Surface *surface);
            void execute(SDL_Renderer *renderer, TextureStore &store);
            bool isFinished();
        private:
            std::string imageId;
            SDL_Surface *sdlSurface;
            bool finished = false;
            std::shared_timed_mutex finishedMutex;
    };
}
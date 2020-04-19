#pragma once

#include <SDL.h>

namespace dte {
    class TextureJob {
        public:
            TextureJob(SDL_Surface *surface);
        private:
            SDL_Surface *sdlSurface;
    };
}
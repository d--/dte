#pragma once

#include <SDL.h>
#include <string>

namespace dte {
    class TextureJob {
        public:
            TextureJob(std::string id, SDL_Surface *surface);
            std::string getImageID();
            SDL_Texture *convertSurface(SDL_Renderer *renderer);
        private:
            std::string imageId;
            SDL_Surface *sdlSurface;
    };
}
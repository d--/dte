#pragma once
#include <SDL.h>

namespace dte {
    class Texture {
        public:
            Texture(SDL_Texture *d);
            ~Texture();
            int getWidth();
            int getHeight();
        private:
            SDL_Texture *data;
            int width;
            int height;
    };
}

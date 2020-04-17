#include "texture.h"

namespace dte {
    Texture::Texture(SDL_Texture *d) :
        data(d) {}

    Texture::~Texture() {}

    int Texture::getWidth() {
        return width;
    }

    int Texture::getHeight() {
        return height;
    }
}
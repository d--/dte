#include <SDL_image.h>
#include "display_manager.h"

namespace dte {
    DisplayManager::DisplayManager(SDL_Renderer *renderer) :
            cachedWidth(-1),
            cachedHeight(-1),
            renderer(renderer) {}

    SDL_Renderer *DisplayManager::getRenderer() {
        return renderer;
    }

    void DisplayManager::setCachedDimensions(Sint32 w, Sint32 h) {
        cachedWidth = w;
        cachedHeight = h;
    }

    Sint32 DisplayManager::getCachedWindowWidth() const {
        return cachedWidth;
    }

    Sint32 DisplayManager::getCachedWindowHeight() const {
        return cachedHeight;
    }
}
#pragma once

namespace dte {
    class DisplayManager {
    public:
        explicit DisplayManager(SDL_Renderer *renderer);
        SDL_Renderer *getRenderer();
        void setCachedDimensions(Sint32 w, Sint32 h);
        [[nodiscard]] Sint32 getCachedWindowWidth() const;
        [[nodiscard]] Sint32 getCachedWindowHeight() const;
    private:
        SDL_Renderer *renderer;
        Sint32 cachedWidth;
        Sint32 cachedHeight;
    };
}
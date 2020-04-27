#pragma once

#include <SDL.h>

namespace dte {
    class GameState {
    public:
        virtual void enter() = 0;
        virtual void input(SDL_Event event) = 0;
        virtual void update() = 0;
        virtual void draw(SDL_Renderer *renderer, Uint32 totalTimeMs,
                          float remainderFrames) = 0;
        virtual void exit() = 0;
    };
}

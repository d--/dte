#pragma once

#include <SDL.h>
#include "../component/draw.h"

namespace dte {
    class DrawComponent;
    class Entity {
        public:
            Entity(DrawComponent *drawComponent);
            void update();
            void draw(SDL_Renderer *renderer);
        private:
            DrawComponent *drawComponent;
    };
}
#pragma once

#include <SDL.h>
#include "../component/draw.h"
#include "../component/input.h"

namespace dte {
    class InputComponent;
    class DrawComponent;
    class Entity {
        public:
            Entity(InputComponent *inputComponent,
                DrawComponent *drawComponent);
            void input(SDL_Event event);
            void update();
            void draw(SDL_Renderer *renderer);
        private:
            InputComponent *inputComponent;
            DrawComponent *drawComponent;
    };
}
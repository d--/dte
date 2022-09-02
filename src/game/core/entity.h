#pragma once

#include <SDL2/SDL.h>
#include "../component/input.h"
#include "../component/transform.h"
#include "../component/draw.h"

namespace dte {
    class InputComponent;
    class TransformComponent;
    class DrawComponent;
    class Entity {
        public:
            Entity(InputComponent *inputComponent,
                TransformComponent *transformComponent,
                DrawComponent *drawComponent);
            ~Entity();
            void input(SDL_Event event);
            void update();
            void draw(SDL_Renderer *renderer, Uint32 totalTimeMs,
                float remainderFrames);
        private:
            InputComponent *inputComponent;
            TransformComponent *transformComponent;
            DrawComponent *drawComponent;
    };
}
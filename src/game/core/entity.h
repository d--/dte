#pragma once

#include <SDL2/SDL.h>
#include "../component/state.h"
#include "../component/input.h"
#include "../component/transform.h"
#include "../component/draw.h"
#include "../manager/display_manager.h"

namespace dte {
    class InputComponent;
    class TransformComponent;
    class DrawComponent;
    class Entity {
        public:
            Entity(StateComponent *stateComponent,
                InputComponent *inputComponent,
                TransformComponent *transformComponent,
                DrawComponent *drawComponent);
            ~Entity();
            void input(SDL_Event event);
            void update();
            void draw(DisplayManager *dm,
                      Uint32 totalTimeMs, float remainderFrames);
        private:
            StateComponent *stateComponent;
            InputComponent *inputComponent;
            TransformComponent *transformComponent;
            DrawComponent *drawComponent;
    };
}
#pragma once

#include <SDL2/SDL.h>
#include "../component/input.h"
#include "../component/transform.h"
#include "../component/gui.h"
#include "../component/draw.h"
#include "../manager/display_manager.h"

namespace dte {
    class InputComponent;
    class TransformComponent;
    class DrawComponent;
    class GuiComponent;
    class Entity {
        public:
            Entity(InputComponent *inputComponent,
                TransformComponent *transformComponent,
                DrawComponent *drawComponent,
                GuiComponent *guiComponent);
            ~Entity();
            void input(SDL_Event event);
            void update();
            void guiUpdate();
            void draw(DisplayManager *dm,
                      Uint32 totalTimeMs, float remainderFrames);
        private:
            InputComponent *inputComponent;
            TransformComponent *transformComponent;
            DrawComponent *drawComponent;
            GuiComponent *guiComponent;
    };
}
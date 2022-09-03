#pragma once

#include <SDL2/SDL.h>
#include "../core/entity.h"
#include "../manager/display_manager.h"

namespace dte {
    class Entity;
    class DrawComponent {
        public:
            virtual void update(Entity &entity,
                DisplayManager *dm,
                Uint32 totalTimeMs, float remainderFrames) = 0;
            virtual ~DrawComponent() = default;
    };
}
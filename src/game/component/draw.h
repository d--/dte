#pragma once

#include <SDL.h>
#include "../core/entity.h"

namespace dte {
    class Entity;
    class DrawComponent {
        public:
            virtual void update(Entity &entity,
                SDL_Renderer *renderer,
                Uint32 totalTimeMs,
                float remainderFrames) = 0;
            virtual ~DrawComponent() = default;
    };
}
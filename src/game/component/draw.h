#pragma once

#include <SDL.h>
#include "../core/entity.h"

namespace dte {
    class Entity;
    class DrawComponent {
        public:
            virtual void update(Entity &entity, SDL_Renderer *renderer);
            virtual ~DrawComponent();
    };
}
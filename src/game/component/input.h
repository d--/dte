#pragma once

#include "../core/entity.h"

namespace dte {
    class Entity;
    class InputComponent {
        public:
            virtual void update(Entity &entity, SDL_Event event) = 0;
            virtual ~InputComponent() = default;
    };
}
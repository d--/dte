#pragma once

#include "../core/entity.h"

namespace dte {
    class Entity;
    class GuiComponent {
        public:
            virtual void update(Entity &entity) = 0;
            virtual ~GuiComponent() = default;
    };
}

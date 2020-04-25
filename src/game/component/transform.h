#pragma once

#include "../core/entity.h"

namespace dte {
    class Entity;
    class TransformComponent {
        public:
            virtual void update(Entity &entity);
            virtual ~TransformComponent();
    };
}
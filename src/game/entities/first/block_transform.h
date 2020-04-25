#pragma once

#include "../../component/transform.h"
#include "block_input.h"

namespace dte {
    class BlockTransformComponent : public TransformComponent {
        public:
            BlockTransformComponent(BlockInputComponent *bic);
            void update(Entity &entity);
            float getX();
            float getY();
        private:
            BlockInputComponent *blockInputComponent;
            float x = 0, y = 0;
    };
}
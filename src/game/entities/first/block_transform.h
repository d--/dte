#pragma once

#include "../../component/transform.h"
#include "block_input.h"

namespace dte {
    class BlockTransformComponent : public TransformComponent {
        public:
            explicit BlockTransformComponent(BlockInputComponent *bic);
            void update(Entity &entity) override;
            float getX() const;
            float getY() const;
            float getXDelta() const;
            float getYDelta() const;
        private:
            BlockInputComponent *blockInputComponent;
            float x = 0;
            float y = 0;
            float xDelta = 0;
            float yDelta = 0;
    };
}
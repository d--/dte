#pragma once

#include "../../component/transform.h"
#include "block_input.h"

namespace dte {
    class BlockTransformComponent : public TransformComponent {
        public:
            explicit BlockTransformComponent(BlockInputComponent *bic);
            void update(Entity &entity) override;
            [[nodiscard]] float getX() const;
            [[nodiscard]] float getY() const;
            [[nodiscard]] float getXDelta() const;
            [[nodiscard]] float getYDelta() const;
        private:
            BlockInputComponent *blockInputComponent;
            float x = 0;
            float y = 0;
            float dx = 0;
            float dy = 0;
    };
}
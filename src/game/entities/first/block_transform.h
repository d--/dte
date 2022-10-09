#pragma once

#include "../../component/transform.h"
#include "block_input.h"

namespace dte {
    class BlockTransformComponent : public TransformComponent {
        public:
            explicit BlockTransformComponent(BlockStateComponent *bsc);
            void update(Entity &entity) override;
        private:
            BlockStateComponent *state;
    };
}
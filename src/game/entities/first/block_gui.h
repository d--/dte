#pragma once

#include "block_transform.h"

namespace dte {
    class BlockGuiComponent : public GuiComponent {
        public:
            BlockGuiComponent(BlockTransformComponent *btc);
            void update(Entity &entity) override;
        private:
            BlockTransformComponent *blockTransformComponent;
    };
}
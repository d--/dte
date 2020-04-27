#pragma once

#include "../../component/draw.h"
#include "block_transform.h"

namespace dte {
    class BlockDrawComponent : public DrawComponent {
        public:
            BlockDrawComponent(BlockTransformComponent *btc, SDL_Texture *tex);
            void update(Entity &entity, SDL_Renderer *renderer,
                Uint32 totalTimeMs, float remainderFrames) override;
        private:
            BlockTransformComponent *blockTransformComponent;
            SDL_Texture *texture;
            SDL_Rect rect;
    };
}
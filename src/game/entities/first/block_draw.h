#pragma once

#include "../../component/draw.h"
#include "block_transform.h"

namespace dte {
    class BlockDrawComponent : public DrawComponent {
        public:
            BlockDrawComponent(BlockStateComponent *bsc, SDL_Texture *tex);
            void update(Entity &entity,
                        DisplayManager *dm,
                        Uint32 totalTimeMs, float remainderFrames) override;
        private:
            BlockStateComponent *blockStateComponent;
            SDL_Texture *texture;
            SDL_Rect rect;
    };
}
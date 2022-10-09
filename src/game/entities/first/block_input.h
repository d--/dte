#pragma once

#include "../../component/input.h"
#include "block_state.h"

namespace dte {
    const unsigned int BLOCK_INPUT_NONE  = 0x0;
    const unsigned int BLOCK_INPUT_RIGHT = 0x1;
    const unsigned int BLOCK_INPUT_LEFT  = 0x2;
    const unsigned int BLOCK_INPUT_UP    = 0x4;
    const unsigned int BLOCK_INPUT_DOWN  = 0x8;

    class BlockInputComponent : public InputComponent {
        public:
            explicit BlockInputComponent(BlockStateComponent *bsc);
            void update(Entity &entity, SDL_Event event) override;
        private:
            BlockStateComponent *state;
    };
}

#pragma once

#include "../../component/input.h"

namespace dte {
    const unsigned int BLOCK_INPUT_NONE  = 0x0;
    const unsigned int BLOCK_INPUT_RIGHT = 0x1;
    const unsigned int BLOCK_INPUT_LEFT  = 0x2;
    const unsigned int BLOCK_INPUT_UP    = 0x4;
    const unsigned int BLOCK_INPUT_DOWN  = 0x8;

    class BlockInputComponent : public InputComponent {
        public:
            void update(Entity &entity, SDL_Event event) override;
            unsigned int getBlockInputState() const;
        private:
            unsigned int inputState = 0;
    };
}
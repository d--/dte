#pragma once

#include "../../component/state.h"

namespace dte {
    class BlockStateComponent : public StateComponent {
    public:
        bool showUi = true;
        bool fast = false;
        bool rotate = true;

        unsigned int inputState = 0;

        float x = 0;
        float y = 0;
        float dx = 0;
        float dy = 0;
    };
}

#pragma once

#include "../../component/state.h"

namespace dte {
    class BlockStateComponent : public StateComponent {
    public:
        bool showUi = true;
        bool rotate = true;

        unsigned int inputState = 0;

        float x = 0;
        float y = 0;
        float dx = 0;
        float dy = 0;
        bool fast = false;
        bool forceCentered = false;
        bool rainbow = false;
        float rgbMod[3] = {1.f, 1.f, 1.f};
    };
}

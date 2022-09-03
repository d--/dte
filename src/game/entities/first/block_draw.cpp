#include "block_draw.h"
#include "../../core/constants.h"
#include <cmath>

namespace dte {
    BlockDrawComponent::BlockDrawComponent(BlockTransformComponent *btc,
            SDL_Texture *tex) :
        blockTransformComponent(btc),
        texture(tex),
        rect(SDL_Rect{
            0, 0,
            128, 128
        }) {}

    void BlockDrawComponent::update(Entity &entity,
                                    DisplayManager *dm,
                                    Uint32 totalTimeMs, float remainderFrames) {
        float time = float(totalTimeMs) + (FIXED_MS_UPDATE * remainderFrames);

        float slowFactor = 1000.f; // ms per cycle
        float scale = 50.f;
        float scaleWDelta = sin((time * (PI * 2.f)) / slowFactor) * scale;
        float scaleHDelta = sin((time * (PI * 2.f)) / (slowFactor * 0.44f)) * 20.f;
        float rotDelta = sin((time * (PI * 2.f)) / (slowFactor * 1.2f)) * 15.f;

        float x = blockTransformComponent->getX();
        float y = blockTransformComponent->getY();
        float xDelta = blockTransformComponent->getXDelta();
        float yDelta = blockTransformComponent->getYDelta();

        rect.w = int(128.f + scaleWDelta);
        rect.h = int(128.f + scaleHDelta);
        rect.x = int(x + (xDelta * (remainderFrames - 1)) - (scaleWDelta / 2.f));
        rect.y = int(y + (yDelta * (remainderFrames - 1)) - (scaleHDelta / 2.f));

        SDL_RenderCopyEx(dm->getRenderer(), texture, nullptr, &rect, rotDelta,
            nullptr, SDL_FLIP_NONE);
    }
}
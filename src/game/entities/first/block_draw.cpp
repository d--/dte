#include "block_draw.h"
#include <cmath>

namespace dte {
    const int FIXED_MS_UPDATE = 15;
    const float PI = 3.1415926535f;

    BlockDrawComponent::BlockDrawComponent(BlockTransformComponent *btc,
            SDL_Texture *tex) :
        blockTransformComponent(btc),
        texture(tex),
        rect(SDL_Rect{
            0, 0,
            128, 128
        }) {}

    void BlockDrawComponent::update(Entity &entity, SDL_Renderer *renderer, 
            Uint32 totalTimeMs, float remainderFrames) {
        float time = float(totalTimeMs) + (FIXED_MS_UPDATE * remainderFrames);
        float slow = 250.f;
        float scale = 50.f;
        int scaleWDelta = int(sin((time * (PI/2)) / slow) * scale);
        int scaleHDelta = int(sin((time * (PI/2)) / 110.f) * 20.f);
        int rotDelta = int(sin((time * (PI/2)) / 400.f) * 15.f);
        rect.w = 128 + scaleWDelta;
        rect.h = 128 + scaleHDelta;
        float x = blockTransformComponent->getX();
        float y = blockTransformComponent->getY();
        float xDelta = blockTransformComponent->getXDelta();
        float yDelta = blockTransformComponent->getYDelta();
        rect.x = int(x + (xDelta * remainderFrames)) - (scaleWDelta / 2);
        rect.y = int(y + (yDelta * remainderFrames)) - (scaleHDelta / 2);
        SDL_RenderCopyEx(renderer, texture, nullptr, &rect, rotDelta,
            nullptr, SDL_FLIP_NONE);
    }
}
#include "block_draw.h"
#include <cmath>
#include <iostream>

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
        int time = totalTimeMs + int(FIXED_MS_UPDATE * remainderFrames);
        float slow = 400.f;
        float scale = 20.f;
        int scaleWDelta = int(sin((time * (PI/2)) / slow) * scale);
        int scaleHDelta = int(sin((time * (PI/2)) / 400.f) * 20.f);
        int rotDelta = int(sin((time * (PI/2)) / 800.f) * 10.f);
        rect.w = 128 + scaleWDelta;
        rect.h = 128 + scaleHDelta;
        rect.x = blockTransformComponent->getX();
        rect.y = blockTransformComponent->getY();
        SDL_RenderCopyEx(renderer, texture, nullptr, &rect, rotDelta,
            nullptr, SDL_FLIP_NONE);
    }
}
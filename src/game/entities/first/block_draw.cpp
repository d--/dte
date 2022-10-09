#include "block_draw.h"
#include "../../core/constants.h"
#include <cmath>
#include "../../../imgui/imgui.h"

namespace dte {
    BlockDrawComponent::BlockDrawComponent(BlockStateComponent *bsc,
            SDL_Texture *tex) :
        blockStateComponent(bsc),
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
        float scale = 25.f;
        float scaleWDelta = sin((time * (PI * 2.f)) / slowFactor) * scale;
        float scaleHDelta = sin((time * (PI * 2.f)) / (slowFactor * 0.44f)) * 10.f;
        float rotDelta = sin((time * (PI * 2.f)) / (slowFactor * 1.2f)) * 7.5f;

        float x = blockStateComponent->x;
        float y = blockStateComponent->y;
        float xDelta = blockStateComponent->dx;
        float yDelta = blockStateComponent->dy;

        rect.w = int(128.f + scaleWDelta);
        rect.h = int(128.f + scaleHDelta);
        rect.x = int(x + (xDelta * (remainderFrames - 1)) - (scaleWDelta / 2.f));
        rect.y = int(y + (yDelta * (remainderFrames - 1)) - (scaleHDelta / 2.f));

        ImGui::Begin("Block Transform Properties");
        ImGui::Text("x = %f", blockStateComponent->x);
        ImGui::Text("y = %f", blockStateComponent->y);
        ImGui::Text("dx = %f", blockStateComponent->dx);
        ImGui::Text("dy = %f", blockStateComponent->dy);
        ImGui::End();

        ImGui::Begin("Block Draw Rect Properties");
        ImGui::Text("w = %d", rect.w);
        ImGui::Text("h = %d", rect.h);
        ImGui::Text("x = %d", rect.x);
        ImGui::Text("y = %d", rect.y);
        ImGui::Text("rot = %f", rotDelta);
        ImGui::Checkbox("Rotate", &(blockStateComponent->rotate));
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                    1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
        ImGui::End();

        if (!(blockStateComponent->rotate)) {
            rotDelta = 0;
        }

        SDL_RenderCopyEx(dm->getRenderer(), texture, nullptr, &rect, rotDelta,
            nullptr, SDL_FLIP_NONE);
    }
}
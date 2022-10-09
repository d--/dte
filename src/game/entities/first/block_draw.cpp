#include "block_draw.h"
#include "../../core/constants.h"
#include <cmath>
#include "../../../imgui/imgui.h"

namespace dte {
    BlockDrawComponent::BlockDrawComponent(BlockStateComponent *bsc,
            SDL_Texture *tex) :
        state(bsc),
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

        float x = state->x;
        float y = state->y;
        float xDelta = state->dx;
        float yDelta = state->dy;

        rect.w = int(128.f + scaleWDelta);
        rect.h = int(128.f + scaleHDelta);
        rect.x = int(x + (xDelta * (remainderFrames - 1)) - (scaleWDelta / 2.f));
        rect.y = int(y + (yDelta * (remainderFrames - 1)) - (scaleHDelta / 2.f));

        if (state->showUi) {
            ImGui::Begin("Block Transform Properties");
            ImGui::Text("x = %f", state->x);
            ImGui::Text("y = %f", state->y);
            ImGui::Text("dx = %f", state->dx);
            ImGui::Text("dy = %f", state->dy);
            ImGui::Checkbox("Go Fast", &(state->fast));
            ImGui::End();

            ImGui::Begin("Block Draw Rect Properties");
            ImGui::Text("w = %d", rect.w);
            ImGui::Text("h = %d", rect.h);
            ImGui::Text("x = %d", rect.x);
            ImGui::Text("y = %d", rect.y);
            ImGui::Text("rot = %f", rotDelta);
            ImGui::Checkbox("Rotate", &(state->rotate));
            ImGui::Checkbox("Rainbow", &(state->rainbow));
            ImGui::ColorEdit3("Color", state->rgbMod, 0);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate,
                        ImGui::GetIO().Framerate);
            ImGui::End();
        }

        if (!(state->rotate)) {
            rotDelta = 0;
        }

        if (state->forceCentered) {
            rect.x = (dm->getCachedWindowWidth() - rect.w) / 2;
            rect.y = (dm->getCachedWindowHeight() - rect.h) / 2;
        }

        if (state->rainbow) {
            Uint8 r = floor(fabs(sin((time * (PI * 2.f)) / slowFactor) * 200) + 55);
            Uint8 g = floor(fabs(sin((time * (PI * 2.f)) / slowFactor * 0.3f) * 200) + 55);
            Uint8 b = floor(fabs(sin((time * (PI * 2.f)) / slowFactor * 0.66f) * 200) + 55);
            SDL_SetTextureColorMod(texture, r, g, b);
        } else {
            SDL_SetTextureColorMod(texture,
                                   floor(state->rgbMod[0] * 255.f),
                                   floor(state->rgbMod[1] * 255.f),
                                   floor(state->rgbMod[2] * 255.f));
        }

        SDL_RenderCopyEx(dm->getRenderer(), texture, nullptr, &rect, rotDelta,
            nullptr, SDL_FLIP_NONE);
    }
}

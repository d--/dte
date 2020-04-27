#pragma once

#include <vector>
#include "game_state.h"
#include "../core/entity.h"
#include "../asset/asset_manager.h"

namespace dte {
    class SandboxState : public GameState {
    public:
        explicit SandboxState(
                std::unordered_map<std::string, SDL_Texture *> textures);
        void enter() override;
        void input(SDL_Event event) override;
        void update() override;
        void draw(SDL_Renderer *renderer, Uint32 totalTimeMs,
                  float remainderFrames) override;
        void exit() override;
    private:
        std::vector<Entity *> entities;
    };
}
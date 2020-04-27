#pragma once

#include "game_state.h"
#include "../asset/asset_manager.h"
#include "state_manager.h"

namespace dte {
    class GameLoad : public GameState {
    public:
        GameLoad(StateManager *sm, AssetManager *am);
        void enter() override;
        void input(SDL_Event event) override;
        void update() override;
        void draw(SDL_Renderer *renderer, Uint32 totalTimeMs,
                  float remainderFrames) override;
        void exit() override;
    private:
        AssetManager *assetManager;
        StateManager *stateManager;
    };
}

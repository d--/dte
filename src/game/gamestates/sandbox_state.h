#pragma once

#include <vector>
#include "game_state.h"
#include "../core/entity.h"
#include "../asset/asset_manager.h"
#include "generic_loading.h"

namespace dte {
    class SandboxState : public GameState {
    public:
        enum LoadingState {
            LOAD_BEGIN,
            LOAD_IN_PROGRESS,
            LOAD_COMPLETE,
            LOAD_END
        };

        void load(AssetManager *assetManager) override;
        bool isLoading() override;
        void enter() override;
        void input(SDL_Event event) override;
        void update() override;
        void draw(SDL_Renderer *renderer, Uint32 totalTimeMs,
                  float remainderFrames) override;
        bool isQuit() override;
        void exit() override;
    private:
        GenericLoadingMachine loadingMachine;
        AssetJobBatch assetJobBatch;
        LoadingState loadingState = LOAD_BEGIN;
        std::vector<Entity *> entities;
    };
}
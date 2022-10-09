#pragma once

#include <SDL2/SDL.h>
#include <stack>
#include "game_state.h"
#include "../manager/display_manager.h"

namespace dte {
    enum StateManagerState {
        STATE_LOADING,
        STATE_UPDATING
    };

    class StateManager {
    public:
        explicit StateManager(AssetManager *assetManager,
                              DisplayManager *displayManager);
        void push(GameState *state);
        void input(SDL_Event event);
        void update();
        void draw(Uint32 totalTimeMs, float remainderFrames);
    private:
        AssetManager *assetManager;
        DisplayManager *displayManager;
        std::deque<GameState *> states;
        StateManagerState stateManagerState = STATE_LOADING;
    };
}
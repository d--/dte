#pragma once

#include <SDL.h>
#include <stack>
#include "game_state.h"

namespace dte {
    enum StateManagerState {
        STATE_LOADING,
        STATE_UPDATING
    };

    class StateManager {
    public:
        explicit StateManager(AssetManager *assetManager);
        void push(GameState *state);
        void input(SDL_Event event);
        void update();
        void draw(SDL_Renderer *renderer, Uint32 totalTimeMs,
                  float remainderFrames);
    private:
        AssetManager *assetManager;
        std::deque<GameState *> states;
        StateManagerState stateManagerState = STATE_LOADING;
    };
}
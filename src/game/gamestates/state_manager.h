#pragma once

#include <SDL.h>
#include <stack>
#include "game_state.h"

namespace dte {
    enum StateManagerState {
        STATE_UPDATING,
        STATE_PUSHING,
        STATE_POPPING,
        STATE_POST_POP
    };

    class StateManager {
    public:
        void push(GameState *state);
        void input(SDL_Event event);
        void update();
        void draw(SDL_Renderer *renderer, Uint32 totalTimeMs,
                  float remainderFrames);
        void pop();
    private:
        std::stack<GameState *> states;
        GameState *next = nullptr;
        StateManagerState stateManagerState = STATE_UPDATING;
    };
}
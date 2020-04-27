#include "state_manager.h"

namespace dte {
    void StateManager::push(GameState *state) {
        next = state;
        stateManagerState = STATE_PUSHING;
    }

    void StateManager::pop() {
        stateManagerState = STATE_POPPING;
    }

    void StateManager::input(SDL_Event event) {
        if (!states.empty()) {
            states.top()->input(event);
        }
    }

    void StateManager::update() {
        if (stateManagerState == STATE_PUSHING) {
            states.push(next);
            states.top()->enter();
            stateManagerState = STATE_UPDATING;
            return;
        }

        if (stateManagerState == STATE_POPPING) {
            states.top()->exit();
            states.pop();
            stateManagerState = STATE_POST_POP;
            return;
        }

        if (stateManagerState == STATE_POST_POP) {
            states.top()->enter();
            stateManagerState = STATE_UPDATING;
            return;
        }

        states.top()->update();
    }

    void StateManager::draw(SDL_Renderer *renderer, Uint32 totalTimeMs,
                            float remainderFrames) {
        if (!states.empty()) {
            states.top()->draw(renderer, totalTimeMs, remainderFrames);
        }
    }
}
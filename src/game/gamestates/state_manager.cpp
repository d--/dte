#include "state_manager.h"

namespace dte {
    StateManager::StateManager(AssetManager *assetManager) :
        assetManager(assetManager) {}

    void StateManager::push(GameState *state) {
        states.push_back(state);
        stateManagerState = STATE_LOADING;
    }

    void StateManager::input(SDL_Event event) {
        states.back()->input(event);
    }

    void StateManager::update() {
        if (states.back()->isQuit()) {
            states.back()->exit();
            states.pop_back();
            stateManagerState = STATE_LOADING;
            return;
        }

        if (stateManagerState == STATE_LOADING) {
            if (states.back()->isLoading()) {
                states.back()->load(assetManager);
                return;
            }

            states.back()->enter();
            stateManagerState = STATE_UPDATING;
            return;
        }

        states.back()->update();
    }

    void StateManager::draw(SDL_Renderer *renderer, Uint32 totalTimeMs,
                            float remainderFrames) {
        states.back()->draw(renderer, totalTimeMs, remainderFrames);
    }
}
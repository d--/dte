#include "block_input.h"

namespace dte {
    void BlockInputComponent::update(Entity &entity, SDL_Event event) {
        switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_w:
                        inputState |= BLOCK_INPUT_UP;
                        break;
                    case SDLK_a:
                        inputState |= BLOCK_INPUT_LEFT;
                        break;
                    case SDLK_s:
                        inputState |= BLOCK_INPUT_DOWN;
                        break;
                    case SDLK_d:
                        inputState |= BLOCK_INPUT_RIGHT;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym) {
                    case SDLK_w:
                        inputState ^= BLOCK_INPUT_UP;
                        break;
                    case SDLK_a:
                        inputState ^= BLOCK_INPUT_LEFT;
                        break;
                    case SDLK_s:
                        inputState ^= BLOCK_INPUT_DOWN;
                        break;
                    case SDLK_d:
                        inputState ^= BLOCK_INPUT_RIGHT;
                        break;
                }
                break;
        }
    }

    unsigned int BlockInputComponent::getBlockInputState() {
        return inputState;
    }
}
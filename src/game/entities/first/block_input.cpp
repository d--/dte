#include "block_input.h"

namespace dte {
    BlockInputComponent::BlockInputComponent(BlockStateComponent *bsc) :
        state(bsc) {}

    void BlockInputComponent::update(Entity &entity, SDL_Event event) {
        switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_w:
                        state->inputState |= BLOCK_INPUT_UP;
                        break;
                    case SDLK_a:
                        state->inputState |= BLOCK_INPUT_LEFT;
                        break;
                    case SDLK_s:
                        state->inputState |= BLOCK_INPUT_DOWN;
                        break;
                    case SDLK_d:
                        state->inputState |= BLOCK_INPUT_RIGHT;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym) {
                    case SDLK_w:
                        state->inputState ^= BLOCK_INPUT_UP;
                        break;
                    case SDLK_a:
                        state->inputState ^= BLOCK_INPUT_LEFT;
                        break;
                    case SDLK_s:
                        state->inputState ^= BLOCK_INPUT_DOWN;
                        break;
                    case SDLK_d:
                        state->inputState ^= BLOCK_INPUT_RIGHT;
                        break;
                }
                break;
        }
    }
}
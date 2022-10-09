#include "block_input.h"

namespace dte {
    BlockInputComponent::BlockInputComponent(BlockStateComponent *bsc) :
        blockStateComponent(bsc) {}

    void BlockInputComponent::update(Entity &entity, SDL_Event event) {
        switch(event.type) {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) {
                    case SDLK_w:
                        blockStateComponent->inputState |= BLOCK_INPUT_UP;
                        break;
                    case SDLK_a:
                        blockStateComponent->inputState |= BLOCK_INPUT_LEFT;
                        break;
                    case SDLK_s:
                        blockStateComponent->inputState |= BLOCK_INPUT_DOWN;
                        break;
                    case SDLK_d:
                        blockStateComponent->inputState |= BLOCK_INPUT_RIGHT;
                        break;
                }
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym) {
                    case SDLK_w:
                        blockStateComponent->inputState ^= BLOCK_INPUT_UP;
                        break;
                    case SDLK_a:
                        blockStateComponent->inputState ^= BLOCK_INPUT_LEFT;
                        break;
                    case SDLK_s:
                        blockStateComponent->inputState ^= BLOCK_INPUT_DOWN;
                        break;
                    case SDLK_d:
                        blockStateComponent->inputState ^= BLOCK_INPUT_RIGHT;
                        break;
                }
                break;
        }
    }
}
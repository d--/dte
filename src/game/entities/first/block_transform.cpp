#include "block_transform.h"
#include "../../core/constants.h"

namespace dte {
    const float BLOCK_SPEED = 7.f;

    BlockTransformComponent::BlockTransformComponent(BlockStateComponent *bsc) :
        state(bsc) {};

    void BlockTransformComponent::update(Entity &entity) {
        unsigned int input = state->inputState;
        float speed = state->fast ? BLOCK_SPEED * 2.f : BLOCK_SPEED;

        state->dx = 0.f;
        state->dy = 0.f;
        if ((input & BLOCK_INPUT_UP) != 0) {
            state->dy -= speed;
        }
        if ((input & BLOCK_INPUT_DOWN) != 0) {
            state->dy += speed;
        }
        if ((input & BLOCK_INPUT_LEFT) != 0) {
            state->dx -= speed;
        }
        if ((input & BLOCK_INPUT_RIGHT) != 0) {
            state->dx += speed;
        }
        if ((input == (BLOCK_INPUT_UP | BLOCK_INPUT_RIGHT)) ||
                (input == (BLOCK_INPUT_UP | BLOCK_INPUT_LEFT)) ||
                (input == (BLOCK_INPUT_DOWN | BLOCK_INPUT_RIGHT)) ||
                (input == (BLOCK_INPUT_DOWN | BLOCK_INPUT_LEFT))) {
            state->dy = state->dy / SQRT2;
            state->dx = state->dx / SQRT2;
        }
        state->x += state->dx;
        state->y += state->dy;
    }
}
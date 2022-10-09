#include "block_transform.h"
#include "../../core/constants.h"

namespace dte {
    const float BLOCK_SPEED = 7.f;

    BlockTransformComponent::BlockTransformComponent(BlockStateComponent *bsc) :
        blockStateComponent(bsc) {};

    void BlockTransformComponent::update(Entity &entity) {
        unsigned int input = blockStateComponent->inputState;
        blockStateComponent->dx = 0.f;
        blockStateComponent->dy = 0.f;
        if ((input & BLOCK_INPUT_UP) != 0) {
            blockStateComponent->dy -= BLOCK_SPEED;
        }
        if ((input & BLOCK_INPUT_DOWN) != 0) {
            blockStateComponent->dy += BLOCK_SPEED;
        }
        if ((input & BLOCK_INPUT_LEFT) != 0) {
            blockStateComponent->dx -= BLOCK_SPEED;
        }
        if ((input & BLOCK_INPUT_RIGHT) != 0) {
            blockStateComponent->dx += BLOCK_SPEED;
        }
        if ((input == (BLOCK_INPUT_UP | BLOCK_INPUT_RIGHT)) ||
                (input == (BLOCK_INPUT_UP | BLOCK_INPUT_LEFT)) ||
                (input == (BLOCK_INPUT_DOWN | BLOCK_INPUT_RIGHT)) ||
                (input == (BLOCK_INPUT_DOWN | BLOCK_INPUT_LEFT))) {
            blockStateComponent->dy = blockStateComponent->dy / SQRT2;
            blockStateComponent->dx = blockStateComponent->dx / SQRT2;
        }
        blockStateComponent->x += blockStateComponent->dx;
        blockStateComponent->y += blockStateComponent->dy;
    }
}
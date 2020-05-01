#include "block_transform.h"
#include "../../core/constants.h"

namespace dte {
    const float BLOCK_SPEED = 7.f;

    BlockTransformComponent::BlockTransformComponent(
            BlockInputComponent *bic) :
        blockInputComponent(bic) {};

    void BlockTransformComponent::update(Entity &entity) {
        unsigned int input = blockInputComponent->getBlockInputState();
        dx = 0.f;
        dy = 0.f;
        if ((input & BLOCK_INPUT_UP) != 0) {
            dy -= BLOCK_SPEED;
        }
        if ((input & BLOCK_INPUT_DOWN) != 0) {
            dy += BLOCK_SPEED;
        }
        if ((input & BLOCK_INPUT_LEFT) != 0) {
            dx -= BLOCK_SPEED;
        }
        if ((input & BLOCK_INPUT_RIGHT) != 0) {
            dx += BLOCK_SPEED;
        }
        if ((input == (BLOCK_INPUT_UP | BLOCK_INPUT_RIGHT)) ||
                (input == (BLOCK_INPUT_UP | BLOCK_INPUT_LEFT)) ||
                (input == (BLOCK_INPUT_DOWN | BLOCK_INPUT_RIGHT)) ||
                (input == (BLOCK_INPUT_DOWN | BLOCK_INPUT_LEFT))) {
            dy = dy / SQRT2;
            dx = dx / SQRT2;
        }
        x += dx;
        y += dy;
    }

    float BlockTransformComponent::getX() const {
        return x;
    }

    float BlockTransformComponent::getY() const {
        return y;
    }

    float BlockTransformComponent::getXDelta() const {
        return dx;
    }

    float BlockTransformComponent::getYDelta() const {
        return dy;
    }
}
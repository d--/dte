#include "block_transform.h"
#include "../../core/constants.h"

namespace dte {
    const float BLOCK_SPEED = 7.f;

    BlockTransformComponent::BlockTransformComponent(
            BlockInputComponent *bic) :
        blockInputComponent(bic) {};

    void BlockTransformComponent::update(Entity &entity) {
        unsigned int input = blockInputComponent->getBlockInputState();
        xDelta = 0.f;
        yDelta = 0.f;
        if ((input & BLOCK_INPUT_UP) != 0) {
            yDelta -= BLOCK_SPEED;
        }
        if ((input & BLOCK_INPUT_DOWN) != 0) {
            yDelta += BLOCK_SPEED;
        }
        if ((input & BLOCK_INPUT_LEFT) != 0) {
            xDelta -= BLOCK_SPEED;
        }
        if ((input & BLOCK_INPUT_RIGHT) != 0) {
            xDelta += BLOCK_SPEED;
        }
        if ((input == (BLOCK_INPUT_UP | BLOCK_INPUT_RIGHT)) ||
                (input == (BLOCK_INPUT_UP | BLOCK_INPUT_LEFT)) ||
                (input == (BLOCK_INPUT_DOWN | BLOCK_INPUT_RIGHT)) ||
                (input == (BLOCK_INPUT_DOWN | BLOCK_INPUT_LEFT))) {
            yDelta = yDelta / SQRT2;
            xDelta = xDelta / SQRT2;
        }
        x += xDelta;
        y += yDelta;
    }

    float BlockTransformComponent::getX() const {
        return x;
    }

    float BlockTransformComponent::getY() const {
        return y;
    }

    float BlockTransformComponent::getXDelta() const {
        return xDelta;
    }

    float BlockTransformComponent::getYDelta() const {
        return yDelta;
    }
}
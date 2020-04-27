#include "block_transform.h"

namespace dte {
    BlockTransformComponent::BlockTransformComponent(
            BlockInputComponent *bic) :
        blockInputComponent(bic) {};

    void BlockTransformComponent::update(Entity &entity) {
        unsigned int input = blockInputComponent->getBlockInputState();
        xDelta = 0.f;
        yDelta = 0.f;
        if ((input & BLOCK_INPUT_UP) != 0) {
            y -= 5.f;
            yDelta = -5.f;
        }
        if ((input & BLOCK_INPUT_DOWN) != 0) {
            y += 5.f;
            yDelta = 5.f;
        }
        if ((input & BLOCK_INPUT_LEFT) != 0) {
            x -= 5.f;
            xDelta = -5.f;
        }
        if ((input & BLOCK_INPUT_RIGHT) != 0) {
            x += 5.f;
            xDelta = 5.f;
        }
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
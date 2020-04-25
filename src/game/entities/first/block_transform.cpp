#include "block_transform.h"

namespace dte {
    BlockTransformComponent::BlockTransformComponent(
            BlockInputComponent *bic) :
        blockInputComponent(bic) {};

    void BlockTransformComponent::update(Entity &entity) {
        unsigned int input = blockInputComponent->getBlockInputState();
        if ((input & BLOCK_INPUT_UP) != 0) {
            y -= 3.f;
        }
        if ((input & BLOCK_INPUT_DOWN) != 0) {
            y += 3.f;
        }
        if ((input & BLOCK_INPUT_LEFT) != 0) {
            x -= 3.f;
        }
        if ((input & BLOCK_INPUT_RIGHT) != 0) {
            x += 3.f;
        }
    }

    float BlockTransformComponent::getX() {
        return x;
    }

    float BlockTransformComponent::getY() {
        return y;
    }
}
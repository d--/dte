#include <unordered_map>
#include "sandbox_state.h"
#include "../entities/first/block_input.h"
#include "../entities/first/block_transform.h"
#include "../entities/first/block_draw.h"

namespace dte {
    void SandboxState::load(AssetManager *assetManager) {
        if (loadingState == LOAD_BEGIN) {
            assetManager->enqueueJob(new ImageLoadJob(
                    "blockA", "../assets/block.png"));
            loadingState = LOAD_IN_PROGRESS;
        }

        if (assetManager->jobQueuesEmpty()) {
            auto blockTex = assetManager->getTexture("blockA");
            auto blockInput = new BlockInputComponent();
            auto blockTransform = new BlockTransformComponent(blockInput);
            auto blockDraw = new BlockDrawComponent(blockTransform, blockTex);
            auto block = new Entity(blockInput, blockTransform, blockDraw);
            entities.push_back(block);

            loadingState = LOAD_COMPLETE;
        }
    }

    void SandboxState::enter() {

    }

    void SandboxState::input(SDL_Event event) {
        for (Entity *entity : entities) {
            entity->input(event);
        }
    }

    void SandboxState::update() {
        for (Entity *entity : entities) {
            entity->update();
        }
    }

    void SandboxState::draw(SDL_Renderer *renderer, Uint32 totalTimeMs,
                            float remainderFrames) {
        for (Entity *entity : entities) {
            entity->draw(renderer, totalTimeMs, remainderFrames);
        }
    }

    bool SandboxState::isQuit() {
        return false;
    }

    void SandboxState::exit() {

    }

    bool SandboxState::isLoading() {
        return loadingState == LOAD_BEGIN || loadingState == LOAD_IN_PROGRESS;
    }
}

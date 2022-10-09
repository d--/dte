#include <unordered_map>
#include "sandbox_state.h"
#include "../entities/first/block_state.h"
#include "../entities/first/block_input.h"
#include "../entities/first/block_transform.h"
#include "../entities/first/block_draw.h"
#include "../job/image_load_job.h"

namespace dte {
    void SandboxState::load(AssetManager *assetManager) {
        if (loadingState == LOAD_BEGIN) {
            assetJobBatch.add(new ImageLoadJob("blockA", "block.png"));
            loadingState = LOAD_IN_PROGRESS;
        }

        if (loadingState == LOAD_IN_PROGRESS) {
            loadingMachine.load(assetManager, &assetJobBatch, &entities);
            if (loadingMachine.isDone()) {
                auto blockTex = assetManager->getTexture("blockA");
                auto blockState = new BlockStateComponent();
                auto blockInput = new BlockInputComponent(blockState);
                auto blockTransform = new BlockTransformComponent(blockState);
                auto blockDraw = new BlockDrawComponent(blockState, blockTex);
                auto block = new Entity(blockState,
                                        blockInput,
                                        blockTransform,
                                        blockDraw);
                entities.push_back(block);
                loadingState = LOAD_COMPLETE;
            }
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

    void SandboxState::draw(DisplayManager *dm,
                            Uint32 totalTimeMs, float remainderFrames) {
        for (Entity *entity : entities) {
            entity->draw(dm, totalTimeMs, remainderFrames);
        }
    }

    bool SandboxState::isQuit() {
        return false;
    }

    void SandboxState::exit() {
        for (Entity *entity : entities) {
            delete entity;
        }
    }

    bool SandboxState::isLoading() {
        return loadingState != LOAD_COMPLETE;
    }
}

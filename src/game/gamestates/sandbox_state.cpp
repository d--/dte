#include <unordered_map>
#include "sandbox_state.h"
#include "../entities/first/block_input.h"
#include "../entities/first/block_transform.h"
#include "../entities/first/block_draw.h"
#include "../entities/first/block_gui.h"
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
                auto blockInput = new BlockInputComponent();
                auto blockTransform = new BlockTransformComponent(blockInput);
                auto blockDraw = new BlockDrawComponent(blockTransform, blockTex);
                auto blockGui = new BlockGuiComponent(blockTransform);
                auto block = new Entity(blockInput,
                                        blockTransform,
                                        blockDraw,
                                        blockGui);
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

    void SandboxState::guiUpdate() {
        for (Entity *entity : entities) {
            entity->guiUpdate();
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

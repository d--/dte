#include <unordered_map>
#include "sandbox_state.h"
#include "../entities/first/block_input.h"
#include "../entities/first/block_transform.h"
#include "../entities/first/block_draw.h"
#include "../job/text_load_job.h"
#include "../job/image_load_job.h"

namespace dte {
    void SandboxState::load(AssetManager *assetManager) {
        if (loadingState == LOAD_BEGIN) {
            loadingJobBatch.add(new TextLoadJob("loadingText",
                                      "Philosopher-Regular.ttf",
                                      "LOADING", 72, 0xFF, 0xFF, 0xFF, 0xFF));
            assetManager->processBatch(&loadingJobBatch);
            loadingState = LOAD_SHOW;
            return;
        }

        if (loadingState == LOAD_SHOW && loadingJobBatch.isFinished()) {
            auto loaderTex = assetManager->getTexture("loadingText");
            auto loaderInput = new BlockInputComponent();
            auto loaderTransform = new BlockTransformComponent(loaderInput);
            auto loaderDraw = new BlockDrawComponent(loaderTransform, loaderTex);
            auto loader = new Entity(loaderInput, loaderTransform, loaderDraw);
            entities.push_back(loader);

            assetJobBatch.add(new ImageLoadJob("blockA", "block.png"));
            assetManager->processBatch(&assetJobBatch);
            loadingState = LOAD_IN_PROGRESS;
            return;
        }

        if (loadingState == LOAD_IN_PROGRESS) {
            for (Entity *entity : entities) {
                entity->update();
            }

            if (assetJobBatch.isFinished()) {
                for (unsigned int i = 0; i < entities.size(); i++) {
                    entities.pop_back();
                }

                auto blockTex = assetManager->getTexture("blockA");
                auto blockInput = new BlockInputComponent();
                auto blockTransform = new BlockTransformComponent(blockInput);
                auto blockDraw = new BlockDrawComponent(blockTransform, blockTex);
                auto block = new Entity(blockInput, blockTransform, blockDraw);
                entities.push_back(block);

                loadingState = LOAD_COMPLETE;
                return;
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
        return loadingState != LOAD_COMPLETE;
    }
}

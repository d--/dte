#include "generic_loading.h"
#include "../job/text_load_job.h"
#include "../entities/first/block_input.h"
#include "../entities/first/block_transform.h"
#include "../entities/first/block_draw.h"

namespace dte {
    void GenericLoadingMachine::load(AssetManager *assetManager,
            AssetJobBatch *batch, std::vector<Entity *> *entities) {
        if (loadingState == LOAD_BEGIN) {
            loadingMachineAssetJobBatch.add(new TextLoadJob("loadingText",
                                                            "Philosopher-Regular.ttf",
                                                            "LOADING", 72, 0xFF, 0xFF, 0xFF, 0xFF));
            assetManager->processBatch(&loadingMachineAssetJobBatch);
            loadingState = LOAD_SHOW;
            return;
        }

        if (loadingState == LOAD_SHOW && loadingMachineAssetJobBatch.isFinished()) {
            assetManager->processBatch(batch);

            auto loaderTex = assetManager->getTexture("loadingText");
            auto loaderState = new BlockStateComponent();
            loaderState->showUi = false;
            loaderState->rotate = false;
            loaderState->forceCentered = true;
            auto loaderInput = new BlockInputComponent(loaderState);
            auto loaderTransform = new BlockTransformComponent(loaderState);
            auto loaderDraw = new BlockDrawComponent(loaderState,
                    loaderTex);
            auto loader = new Entity(loaderState,
                                     loaderInput,
                                     loaderTransform,
                                     loaderDraw);
            entities->push_back(loader);
            loadingState = LOAD_IN_PROGRESS;
            return;
        }

        if (loadingState == LOAD_IN_PROGRESS) {
            for (Entity *entity : *entities) {
                entity->update();
            }

            if (batch->isFinished()) {
                entities->clear();
                loadingState = LOAD_COMPLETE;
                return;
            }
        }
    }

    bool GenericLoadingMachine::isDone() const {
        return loadingState == LOAD_COMPLETE;
    }
}
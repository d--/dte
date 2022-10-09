#pragma once

#include "../job/asset_job_batch.h"
#include "../core/entity.h"

namespace dte {
    class GenericLoadingMachine {
    public:
        enum LoadingState {
            LOAD_BEGIN,
            LOAD_SHOW,
            LOAD_IN_PROGRESS,
            LOAD_COMPLETE
        };

        void load(AssetManager *assetManager, AssetJobBatch *batch,
                  std::vector<Entity *> *entities);
        [[nodiscard]] bool isDone() const;
    private:
        AssetJobBatch loadingMachineAssetJobBatch;
        LoadingState loadingState = LOAD_BEGIN;
    };
}

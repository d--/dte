#pragma once

#include "asset_job.h"

namespace dte {
    class AssetManager;
    class AssetJob;
    class AssetJobBatch {
    public:
        void add(AssetJob *job);
        void execute(AssetManager *manager);
        bool isFinished();
    private:
        std::vector<AssetJob *> assetJobs;
        std::shared_timed_mutex assetJobsMutex;
        bool finished = false;
        std::shared_timed_mutex finishedMutex;
    };
}

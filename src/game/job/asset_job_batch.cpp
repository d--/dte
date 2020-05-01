#include "asset_job_batch.h"

namespace dte {
    void AssetJobBatch::add(AssetJob *job) {
        std::unique_lock lock(assetJobsMutex);
        assetJobs.push_back(job);
    }

    bool AssetJobBatch::isFinished() {
        std::shared_lock lock(finishedMutex);
        return finished;
    }

    void AssetJobBatch::execute(AssetManager *manager) {
        std::shared_lock ajLock(assetJobsMutex);
        for (AssetJob *job : assetJobs) {
            job->execute(manager);
            delete job;
        }

        std::unique_lock fLock(finishedMutex);
        finished = true;
    }
}

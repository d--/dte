#pragma once

#include "asset_job.h"

namespace dte {
    class AssetManager;
    class ImageLoadJob : public AssetJob {
    public:
        ImageLoadJob(std::string id, std::string location);
        void execute(AssetManager *manager) override;
    private:
        std::string imageId;
        std::string imageName;
    };
}

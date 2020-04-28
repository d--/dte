#pragma once

#include "asset_job.h"

namespace dte {
    class ImageLoadJob : public AssetJob {
    public:
        ImageLoadJob(std::string id, std::string location);
        void execute(AssetManager *manager);
    private:
        std::string imageId;
        std::string imageLocation;
    };
}

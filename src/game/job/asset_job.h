#pragma once

#include "../asset/asset_manager.h"

namespace dte {
    class AssetManager;
    class AssetJob {
    public:
        virtual void execute(AssetManager *manager) = 0;
        virtual ~AssetJob() = default;
    };
}

#pragma once

#include <string>
#include <vector>

namespace dte {
    struct asset_image {
        std::string location;
        int width;
        int height;
    };

    std::vector<struct asset_image> assetImages{
        { "assets/block.png", 256, 256 }
    };
}

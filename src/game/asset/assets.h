#pragma once

#include <string>
#include <vector>

namespace dte {
    struct asset_image {
        std::string id;
        std::string location;
        int width;
        int height;
    };

    static std::vector<struct asset_image> assetImages{
        { "blockA", "assets/block.png", 256, 256 }
    };
}

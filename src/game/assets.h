#include <string>
#include <vector>

namespace dte {
    struct asset_texture {
        std::string location;
        int width;
        int height;
    };

    std::vector<struct asset_texture> assetTextures{
        { "assets/block.png", 256, 256 }
    };
}

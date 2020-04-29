#pragma once

#include "asset_job.h"

namespace dte {
    class TextLoadJob : public AssetJob {
    public:
        TextLoadJob(std::string id, std::string font, std::string text, int pt,
                    Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void execute(AssetManager *manager) override;
    private:
        std::string id;
        std::string font;
        std::string text;
        int pt;
        Uint8 r, g, b, a;
    };
}

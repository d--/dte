#pragma once

#include "game_state.h"
#include "../asset/asset_manager.h"

namespace dte {
    class GameLoad : public GameState {
        public:
            GameLoad(AssetManager *am);
            void update();
        private:
            AssetManager *assetManager;
    };
}

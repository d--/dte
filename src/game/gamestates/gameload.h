#pragma once
#include "gamestate.h"
#include "../asset_manager.h"

namespace dte {
    class GameLoad : public GameState {
        public:
            GameLoad(AssetManager *am);
            ~GameLoad();
            void update();
        private:
            AssetManager *assetManager;
    };
}

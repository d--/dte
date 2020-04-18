#pragma once

namespace dte {
    class GameState {
        public:
            GameState();
            virtual ~GameState();
            virtual void update();
    };
}

#include "../../component/input.h"

namespace dte {
    class BlockInputComponent : public InputComponent {
        public:
            void update(Entity &entity, SDL_Event event);
    };
}
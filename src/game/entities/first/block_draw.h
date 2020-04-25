#include "../../component/draw.h"

namespace dte {
    class BlockDrawComponent : public DrawComponent {
        public:
            void update(Entity &entity, SDL_Renderer *renderer);
    };
}
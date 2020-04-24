#include "entity.h"

namespace dte {
    Entity::Entity(DrawComponent *dc) :
        drawComponent(dc) {}
    
    void Entity::draw(SDL_Renderer *renderer) {
        drawComponent->update(*this, renderer);
    }

    void Entity::update() {
        // update more components here
    }
}
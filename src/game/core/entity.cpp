#include "entity.h"

namespace dte {
    Entity::Entity(InputComponent *ic,
            DrawComponent *dc) :
        inputComponent(ic),
        drawComponent(dc) {}

    void Entity::input(SDL_Event event) {
        inputComponent->update(*this, event);
    }

    void Entity::update() {
        // update more components here
    }

    void Entity::draw(SDL_Renderer *renderer) {
        drawComponent->update(*this, renderer);
    }
}
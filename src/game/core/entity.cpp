#include "entity.h"

namespace dte {
    Entity::Entity(InputComponent *ic,
            TransformComponent *tc,
            DrawComponent *dc) :
        inputComponent(ic),
        transformComponent(tc),
        drawComponent(dc) {}

    Entity::~Entity() {
        delete inputComponent;
        delete transformComponent;
        delete drawComponent;
    }

    void Entity::input(SDL_Event event) {
        inputComponent->update(*this, event);
    }

    void Entity::update() {
        transformComponent->update(*this);
    }

    void Entity::draw(SDL_Renderer *renderer, Uint32 totalTimeMs,
            float remainderFrames) {
        drawComponent->update(*this, renderer, totalTimeMs, remainderFrames);
    }
}
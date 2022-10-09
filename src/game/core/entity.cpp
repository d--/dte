#include "entity.h"

namespace dte {
    Entity::Entity(StateComponent *sc,
            InputComponent *ic,
            TransformComponent *tc,
            DrawComponent *dc) :
        stateComponent(sc),
        inputComponent(ic),
        transformComponent(tc),
        drawComponent(dc) {}

    Entity::~Entity() {
        delete inputComponent;
        delete transformComponent;
        delete drawComponent;
        delete stateComponent;
    }

    void Entity::input(SDL_Event event) {
        inputComponent->update(*this, event);
    }

    void Entity::update() {
        transformComponent->update(*this);
    }

    void Entity::draw(DisplayManager *dm,
                      Uint32 totalTimeMs, float remainderFrames) {
        drawComponent->update(*this, dm, totalTimeMs, remainderFrames);
    }
}
#include "entity.h"

namespace dte {
    Entity::Entity(InputComponent *ic,
            TransformComponent *tc,
            DrawComponent *dc,
            GuiComponent *gc) :
        inputComponent(ic),
        transformComponent(tc),
        drawComponent(dc),
        guiComponent(gc) {}

    Entity::~Entity() {
        delete inputComponent;
        delete transformComponent;
        delete drawComponent;
        delete guiComponent;
    }

    void Entity::input(SDL_Event event) {
        inputComponent->update(*this, event);
    }

    void Entity::update() {
        transformComponent->update(*this);
    }

    void Entity::guiUpdate() {
        if (guiComponent != nullptr)
            guiComponent->update(*this);
    }

    void Entity::draw(DisplayManager *dm,
                      Uint32 totalTimeMs, float remainderFrames) {
        drawComponent->update(*this, dm, totalTimeMs, remainderFrames);
    }
}
#include <unordered_map>
#include "sandbox_state.h"
#include "../entities/first/block_input.h"
#include "../entities/first/block_transform.h"
#include "../entities/first/block_draw.h"

namespace dte {
    SandboxState::SandboxState(
            std::unordered_map<std::string, SDL_Texture *> textures) {
        auto *bic = new BlockInputComponent();
        auto *btc = new BlockTransformComponent(bic);
        auto *bdc = new BlockDrawComponent(btc, textures.at("blockA"));
        auto *block = new Entity(bic, btc, bdc);
        entities.push_back(block);
    }

    void SandboxState::enter() {

    }

    void SandboxState::update() {
        for (Entity *entity : entities) {
            entity->update();
        }
    }

    void SandboxState::exit() {

    }

    void SandboxState::input(SDL_Event event) {
        for (Entity *entity : entities) {
            entity->input(event);
        }
    }

    void SandboxState::draw(SDL_Renderer *renderer, Uint32 totalTimeMs,
                            float remainderFrames) {
        for (Entity *entity : entities) {
            entity->draw(renderer, totalTimeMs, remainderFrames);
        }
    }
}

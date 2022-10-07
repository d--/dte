#include "block_gui.h"
#include "../../../imgui/imgui.h"

namespace dte {
    BlockGuiComponent::BlockGuiComponent(BlockTransformComponent *btc) :
        blockTransformComponent(btc) {}

    void BlockGuiComponent::update(Entity &entity) {
        ImGui::Begin("Block Transform Properties");
        ImGui::Text("x = %f", blockTransformComponent->getX());
        ImGui::Text("y = %f", blockTransformComponent->getY());
        ImGui::Text("dx = %f", blockTransformComponent->getXDelta());
        ImGui::Text("dy = %f", blockTransformComponent->getYDelta());
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                    1000.0f / ImGui::GetIO().Framerate,
                    ImGui::GetIO().Framerate);
        ImGui::End();
    }
}
#include "../include/GuiController.hpp"

#include <imgui.h>
#include <engine/graphics/GraphicsController.hpp>
#include <engine/platform/PlatformController.hpp>

namespace app {
    void GUIController::initialize() {
        set_enable(false);
    }

    void GUIController::poll_events() {
        auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
        if (platform->key(engine::platform::KeyId::KEY_F2).state() == engine::platform::Key::State::JustPressed) {
            platform->set_enable_cursor(!is_enabled());
            set_enable(!is_enabled());
        }
    }

    void GUIController::draw() {
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto camera   = graphics->camera();
        graphics->begin_gui();

        ImGui::Begin("Camera info");
        ImGui::Text("Camera position: (%f, %f, %f)", camera->Position.x, camera->Position.y, camera->Position.z);
        ImGui::Text("Use WASD Space/Shift to move around");
        ImGui::Text("Hold R to change the spotlight color to red");
        ImGui::Text("Press G for grayscale after 1s. Lasts for 4s.");
        ImGui::End();

        graphics->end_gui();
    }
} // app

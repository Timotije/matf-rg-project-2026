#include "../include/MyApp.hpp"

#include <GuiController.hpp>
#include <MainController.hpp>
#include <spdlog/spdlog.h>

namespace app {
    void MyApp::app_setup() {
        spdlog::info("App setup complete");
        auto main_controller = register_controller<app::MainController>();
        auto gui_controller = register_controller<app::GUIController>();
        main_controller->after(engine::core::Controller::get<engine::core::EngineControllersEnd>());
        main_controller->before(gui_controller);
    }
}// namespace app
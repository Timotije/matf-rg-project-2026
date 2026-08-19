#include <GuiController.hpp>
#include <MainController.hpp>
#include <engine/graphics/GraphicsController.hpp>
#include <engine/graphics/OpenGL.hpp>
#include <engine/platform/PlatformController.hpp>
#include <engine/resources/ResourcesController.hpp>

namespace app {
class MainPlatformEventObserver : public engine::platform::PlatformEventObserver {
public:
    void on_mouse_move(engine::platform::MousePosition position) override;
};

void MainPlatformEventObserver::on_mouse_move(engine::platform::MousePosition position) {
    auto gui_controller = engine::core::Controller::get<GUIController>();
    if (!gui_controller->is_enabled()) {
        auto camera = engine::core::Controller::get<engine::graphics::GraphicsController>()->camera();
        camera->rotate_camera(position.dx, position.dy);
    }
}

void MainController::initialize() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    platform->register_platform_event_observer(std::make_unique<MainPlatformEventObserver>());
    engine::graphics::OpenGL::enable_depth_testing();
    graphics->init_offscreen_msaa_framebuffers();
    platform->set_enable_cursor(false);
}

bool MainController::loop() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    if (platform->key(engine::platform::KeyId::KEY_ESCAPE).is_down()) {
        return false;
    }
    return true;
}

void MainController::draw_island() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    engine::resources::Model *island = resources->model("island");

    engine::resources::Shader *shader = resources->shader("multiple_lights");

    shader->use();
    shader->set_int("material.diffuse", 0);
    shader->set_int("material.specular", 1);

    shader->set_vec3("viewPos", graphics->camera()->Position);
    shader->set_float("material.shininess", 64.0f);

    shader->set_vec3("dirLight.direction", glm::vec3(0.7f, -1.0f, -0.7f));
    shader->set_vec3("dirLight.ambient", glm::vec3(0.15f, 0.15f, 0.15f));
    shader->set_vec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    shader->set_vec3("dirLight.specular", glm::vec3(0.2f, 0.2f, 0.2f));

    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
    model = glm::scale(model, glm::vec3(0.03f));
    shader->set_mat4("model", model);

    island->draw(shader);
}

void MainController::draw_lighthouse() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    engine::resources::Model *lighthouse = resources->model("lighthouse");

    engine::resources::Shader *shader = resources->shader("multiple_lights");

    shader->use();
    shader->set_int("material.diffuse", 0);
    shader->set_int("material.specular", 1);

    shader->set_vec3("viewPos", graphics->camera()->Position);
    shader->set_float("material.shininess", 64.0f);

    shader->set_vec3("dirLight.direction", glm::vec3(0.7f, -1.0f, -0.7f));
    shader->set_vec3("dirLight.ambient", glm::vec3(0.15f, 0.15f, 0.15f));
    shader->set_vec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    shader->set_vec3("dirLight.specular", glm::vec3(0.2f, 0.2f, 0.2f));

    shader->set_vec3("spotLight.position", glm::vec3(
                                                   -0.0036 * cos(platform->frame_time().current),
                                                   2.0f,
                                                   -5.0 + (-0.0067 * sin(platform->frame_time().current))));
    shader->set_vec3("spotLight.direction",
                     glm::vec3(cos(platform->frame_time().current), 0.0f, sin(platform->frame_time().current)));
    shader->set_vec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
    shader->set_vec3("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->set_vec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    shader->set_float("spotLight.constant", 1.0f);
    shader->set_float("spotLight.linear", 0.09);
    shader->set_float("spotLight.quadratic", 0.032);
    shader->set_float("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
    shader->set_float("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
    if (platform->key(engine::platform::KeyId::KEY_R).state() == engine::platform::Key::State::Pressed) {
        shader->set_bool("buttonPressed", true);
    } else {
        shader->set_bool("buttonPressed", false);
    }

    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.65f, -5.0f));
    model = glm::scale(model, glm::vec3(0.1f));
    shader->set_mat4("model", model);

    lighthouse->draw(shader);
}

void MainController::draw_airballoon() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    engine::resources::Model *airballoon = resources->model("airballoon");

    engine::resources::Shader *shader = resources->shader("multiple_lights");

    shader->use();
    shader->set_int("material.diffuse", 0);
    shader->set_int("material.specular", 1);

    shader->set_vec3("viewPos", graphics->camera()->Position);
    shader->set_float("material.shininess", 64.0f);

    shader->set_vec3("dirLight.direction", glm::vec3(0.7f, -1.0f, -0.7f));
    shader->set_vec3("dirLight.ambient", glm::vec3(0.15f, 0.15f, 0.15f));
    shader->set_vec3("dirLight.diffuse", glm::vec3(0.4f, 0.4f, 0.4f));
    shader->set_vec3("dirLight.specular", glm::vec3(0.2f, 0.2f, 0.2f));

    shader->set_mat4("projection", graphics->projection_matrix());
    shader->set_mat4("view", graphics->camera()->view_matrix());
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(
                                          2.0 * cos(platform->frame_time().current),
                                          2.0f,
                                          -5.0 + 2.0 * sin(platform->frame_time().current)));
    model = glm::scale(model, glm::vec3(0.03f));
    shader->set_mat4("model", model);

    airballoon->draw(shader);
}

void MainController::update_camera() {
    auto gui_controller = engine::core::Controller::get<GUIController>();
    if (gui_controller->is_enabled()) {
        return;
    }
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    auto camera = graphics->camera();
    float dt = platform->dt();
    if (platform->key(engine::platform::KeyId::KEY_W).is_down()) {
        camera->move_camera(engine::graphics::Camera::Movement::FORWARD, dt);
    }
    if (platform->key(engine::platform::KeyId::KEY_S).is_down()) {
        camera->move_camera(engine::graphics::Camera::Movement::BACKWARD, dt);
    }
    if (platform->key(engine::platform::KeyId::KEY_A).is_down()) {
        camera->move_camera(engine::graphics::Camera::Movement::LEFT, dt);
    }
    if (platform->key(engine::platform::KeyId::KEY_D).is_down()) {
        camera->move_camera(engine::graphics::Camera::Movement::RIGHT, dt);
    }
    if (platform->key(engine::platform::KeyId::KEY_LEFT_SHIFT).is_down()) {
        camera->move_camera(engine::graphics::Camera::Movement::DOWN, dt);
    }
    if (platform->key(engine::platform::KeyId::KEY_SPACE).is_down()) {
        camera->move_camera(engine::graphics::Camera::Movement::UP, dt);
    }
}

void MainController::update() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();

    update_camera();

    float dt = platform->dt();
    if (platform->key(engine::platform::KeyId::KEY_G).state() == engine::platform::Key::State::JustPressed) {
        m_pressed = true;
        m_timer = 0.0f;
    }

    if (m_pressed) {
        m_timer += dt;

        if (m_timer >= 1.0f) {
            m_grayscale = true;
        }
        if (m_timer >= 5.0f) {
            m_grayscale = false;
            m_timer = 0.0f;
            m_pressed = false;
        }
    }
}

void MainController::begin_draw() {
    engine::graphics::OpenGL::clear_buffers();
}

void MainController::draw_skybox() {
    auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
    auto skybox = resources->skybox("cloud_skybox");
    auto shader = resources->shader("skybox");
    auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
    graphics->draw_skybox(shader, skybox);
}

void MainController::change_buffer() {
    if (m_grayscale) {
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        graphics->draw_in_multisampled();
    } else {
        engine::graphics::OpenGL::enable_depth_testing();
    }
}

void MainController::use_offscreen_msaa() {
    if (m_grayscale) {
        auto graphics = engine::core::Controller::get<engine::graphics::GraphicsController>();
        auto resources = engine::core::Controller::get<engine::resources::ResourcesController>();
        auto shader = resources->shader("aa_post");
        graphics->offscreen_msaa(shader);
    }
}

void MainController::draw() {
    change_buffer();
    draw_island();
    draw_lighthouse();
    draw_airballoon();
    draw_skybox();
    use_offscreen_msaa();
}

void MainController::end_draw() {
    auto platform = engine::core::Controller::get<engine::platform::PlatformController>();
    platform->swap_buffers();
}
}// namespace app

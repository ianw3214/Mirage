#include "engine.hpp"

#include "graphics/graphics.hpp"
#include "GL/glew.h"
#include <imgui.h>

// TODO: Custom keycodes so no need to include SDL
#include <SDL2/SDL.h>

class SandboxState : public Mirage::State {
public:
    void Init() {
        Mirage::ApplicationManager::GetCamera()->SetPosition(0.f, 3.f, 5.f);
        loader.loadModel("res/test.obj");

        terrain1 = new Terrain(0, 0);
        terrain2 = new Terrain(0, 1);

        m_playerPos = Vec3f{0.f, 0.f, 0.f};
        m_angle = 0.f;
        m_movingCamera = false;
        m_cameraMoveStartAngle = 0.f;
        m_cameraMoveStartX = 0;
    }
    void Shutdown() {

    }
    void Update() {
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_W))
        {
            // m_playerPos.z -= 0.01f;
            m_playerPos.x -= std::sin(m_angle) * 0.01f;
            m_playerPos.z -= std::cos(m_angle) * 0.01f;
        }
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_S))
        {
            m_playerPos.x += std::sin(m_angle) * 0.01f;
            m_playerPos.z += std::cos(m_angle) * 0.01f;
        }
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_D))
        {
            m_playerPos.x += std::sin(m_angle + 1.57079632679f) * 0.01f;
            m_playerPos.z += std::cos(m_angle + 1.57079632679f) * 0.01f;
        }
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_A))
        {
            m_playerPos.x += std::sin(m_angle - 1.57079632679f) * 0.01f;
            m_playerPos.z += std::cos(m_angle - 1.57079632679f) * 0.01f;
        }
        if (Mirage::ApplicationManager::GetInput()->LeftMouseClicked())
        {
            m_movingCamera = true;
            m_cameraMoveStartAngle = m_angle;
            m_cameraMoveStartX = Mirage::ApplicationManager::GetInput()->GetMouseX();
        }
        if (Mirage::ApplicationManager::GetInput()->LeftMouseReleased())
        {
            m_movingCamera = false;
        }

        if (m_movingCamera)
        {
            constexpr float sensitivity = 0.005f;
            int offset = m_cameraMoveStartX - Mirage::ApplicationManager::GetInput()->GetMouseX();
            m_angle = m_cameraMoveStartAngle + offset * sensitivity;
        }

        {   // Update the camera
            Vec3f cameraPos = m_playerPos;
            cameraPos.x += std::sin(m_angle) * 5.f;
            cameraPos.y += 3.f;    // Always 3m above ground
            cameraPos.z += std::cos(m_angle) * 5.f;
            Mirage::ApplicationManager::GetCamera()->SetPosition(cameraPos);
            Mirage::ApplicationManager::GetCamera()->SetTarget(m_playerPos);
        }

        ModelRef model = loader.getModel("res/test.obj");
        model->SetPosition(0.f, 1.f, 0.f);
        model->SetScale(1.f);
        Mirage::ApplicationManager::GetRenderer()->DrawModel(model, Mirage::Colours::WHITE);

        Mirage::ApplicationManager::GetRenderer()->DrawModel(terrain1->GetModel(), Mirage::Colours::GREEN);
        Mirage::ApplicationManager::GetRenderer()->DrawModel(terrain2->GetModel(), Mirage::Colours::GREEN);

        {
            ImGui::Begin("Hello world");
            ImGui::Text("This is some useful text.");
            // ImGui::SameLine();
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }
    }
private:
    OBJLoader loader;
    Mirage::Owned<Terrain> terrain1;
    Mirage::Owned<Terrain> terrain2;

    // Camera adjusting code
    // Fix camera up/down angle for now
    Vec3f m_playerPos;
    float m_angle;
    bool m_movingCamera;
    float m_cameraMoveStartAngle;
    int m_cameraMoveStartX;
};

Mirage::WindowConfig Mirage::GetConfiguration()
{
    WindowConfig config("SANDBOX", 1280, 720);
    config.initialState = []() -> Mirage::State* { return new SandboxState(); };
    return config;
}
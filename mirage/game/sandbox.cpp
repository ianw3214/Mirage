#include "engine.hpp"

#include "graphics/graphics.hpp"
#include "GL/glew.h"

// TODO: Custom keycodes so no need to include SDL
#include <SDL2/SDL.h>

#ifdef MIRAGE_EDITOR
#include <imgui-docking/imgui.h>
#endif

constexpr int ticksPerDay = 30000;

class SandboxState : public Mirage::State {
public:
    void Init() {
        Mirage::ApplicationManager::GetCamera()->SetPosition(0.f, 3.f, 5.f);
        loader.loadModel("res/test.obj");

        terrain1 = new Terrain(0, 0);
        terrain2 = new Terrain(0, 1);

        m_playerPos = Vec3f{0.f, 0.f, 0.f};
        m_angleH = 0.f;
        m_angleV = 0.1f;
        m_movingCamera = false;
        m_cameraMoveStartAngleH = 0.f;
        m_cameraMoveStartAngleV = 0.1f;
        m_cameraMoveStartX = 0;
        m_cameraMoveStartY = 0;

        m_timeTick = 0;
    }
    void Shutdown() {

    }
    void Update() {
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_W))
        {
            m_playerPos.x -= std::sin(m_angleH) * 0.01f;
            m_playerPos.z -= std::cos(m_angleH) * 0.01f;
        }
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_S))
        {
            m_playerPos.x += std::sin(m_angleH) * 0.01f;
            m_playerPos.z += std::cos(m_angleH) * 0.01f;
        }
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_D))
        {
            m_playerPos.x += std::sin(m_angleH + 1.57079632679f) * 0.01f;
            m_playerPos.z += std::cos(m_angleH + 1.57079632679f) * 0.01f;
        }
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_A))
        {
            m_playerPos.x += std::sin(m_angleH - 1.57079632679f) * 0.01f;
            m_playerPos.z += std::cos(m_angleH - 1.57079632679f) * 0.01f;
        }
        if (Mirage::ApplicationManager::GetInput()->LeftMouseClicked())
        {
            m_movingCamera = true;
            m_cameraMoveStartAngleH = m_angleH;
            m_cameraMoveStartAngleV = m_angleV;
            m_cameraMoveStartX = Mirage::ApplicationManager::GetInput()->GetMouseX();
            m_cameraMoveStartY = Mirage::ApplicationManager::GetInput()->GetMouseY();
        }
        if (Mirage::ApplicationManager::GetInput()->LeftMouseReleased())
        {
            m_movingCamera = false;
        }

        if (m_movingCamera)
        {
            constexpr float sensitivity = 0.005f;
            int offsetX = m_cameraMoveStartX - Mirage::ApplicationManager::GetInput()->GetMouseX();
            m_angleH = m_cameraMoveStartAngleH + offsetX * sensitivity;
            int offsetY = m_cameraMoveStartY - Mirage::ApplicationManager::GetInput()->GetMouseY();
            m_angleV = m_cameraMoveStartAngleV - offsetY * sensitivity;
            if (m_angleV > 1.57f) m_angleV = 1.57f;
            if (m_angleV < -1.57f) m_angleV = -1.57f;
        }

        {   // Update the camera
            Vec3f cameraPos = m_playerPos;
            cameraPos.x += (std::sin(m_angleH) * (std::cos(m_angleV))) * 10.f;
            cameraPos.y += std::sin(m_angleV) * 10.f;    // Always 3m above ground
            cameraPos.z += (std::cos(m_angleH) * (std::cos(m_angleV))) * 10.f;
            Mirage::ApplicationManager::GetCamera()->SetPosition(cameraPos);
            Mirage::ApplicationManager::GetCamera()->SetTarget(m_playerPos);
        }

        ModelRef model = loader.getModel("res/test.obj");
        model->SetPosition(m_playerPos.x, m_playerPos.y + 1.f, m_playerPos.z);
        model->SetScale(1.f);
        Mirage::ApplicationManager::GetRenderer()->DrawModel(model);

        Mirage::ApplicationManager::GetRenderer()->DrawModel(terrain1->GetModel());
        Mirage::ApplicationManager::GetRenderer()->DrawModel(terrain2->GetModel());

        // Maybe use a curve instead of direct lerp
        // Update clear color for day/night time
        float blue = static_cast<float>(std::abs(m_timeTick * 2 - ticksPerDay)) / static_cast<float>(ticksPerDay);
        Mirage::ApplicationManager::GetRenderer()->ClearColour(0.f, blue * 2.f / 3.f, blue);
        if (++m_timeTick > ticksPerDay)
        {
            m_timeTick = 0;
        }
        #ifdef MIRAGE_EDITOR
        {
            ImGui::Begin("Game");
            ImGui::SliderInt("time of day", &m_timeTick, 0, ticksPerDay);
            ImGui::End();
        }
        #endif
    }
private:
    OBJLoader loader;
    Mirage::Owned<Terrain> terrain1;
    Mirage::Owned<Terrain> terrain2;

    // Camera adjusting code
    Vec3f m_playerPos;
    float m_angleH;
    float m_angleV;
    bool m_movingCamera;
    float m_cameraMoveStartAngleH;
    float m_cameraMoveStartAngleV;
    int m_cameraMoveStartX;
    int m_cameraMoveStartY;

    // Day/night cycle cause why not
    int m_timeTick;
};

Mirage::WindowConfig Mirage::GetConfiguration()
{
    WindowConfig config("SANDBOX", 1280, 720);
    config.initialState = []() -> Mirage::State* { return new SandboxState(); };
    return config;
}
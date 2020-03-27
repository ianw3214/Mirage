#include "engine.hpp"

#include "graphics/graphics.hpp"
#include "GL/glew.h"

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
    }
    void Shutdown() {

    }
    void Update() {
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_W))
        {
            m_playerPos.z -= 0.01f;
        }
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_S))
        {
            m_playerPos.z += 0.01f;
        }
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_D))
        {
            m_playerPos.x += 0.01f;
        }
        if (Mirage::ApplicationManager::GetInput()->KeyPressed(SDL_SCANCODE_A))
        {
            m_playerPos.x -= 0.01f;
        }

        {   // Update the camera
            Vec3f target = m_playerPos;
            target.x += std::sin(m_angle) * 5.f;
            target.y += 3.f;    // Always 3m above ground
            target.z += std::cos(m_angle) * 5.f;
            Mirage::ApplicationManager::GetCamera()->SetPosition(target);
            Mirage::ApplicationManager::GetCamera()->SetTarget(m_playerPos);
        }

        ModelRef model = loader.getModel("res/test.obj");
        model->SetPosition(0.f, 0.f, 0.f);
        model->SetScale(1.f);
        Mirage::ApplicationManager::GetRenderer()->DrawModel(model, Mirage::Colours::WHITE);

        Mirage::ApplicationManager::GetRenderer()->DrawModel(terrain1->GetModel(), Mirage::Colours::RED);
        Mirage::ApplicationManager::GetRenderer()->DrawModel(terrain2->GetModel(), Mirage::Colours::RED);
    }
private:
    OBJLoader loader;
    Mirage::Owned<Terrain> terrain1;
    Mirage::Owned<Terrain> terrain2;

    // Camera adjusting code
    // Fix camera up/down angle for now
    Vec3f m_playerPos;
    float m_angle;
};

Mirage::WindowConfig Mirage::GetConfiguration()
{
    WindowConfig config("SANDBOX", 1280, 720);
    config.initialState = []() -> Mirage::State* { return new SandboxState(); };
    return config;
}
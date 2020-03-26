#include "engine.hpp"

#include "graphics/graphics.hpp"
#include "GL/glew.h"

class SandboxState : public Mirage::State {
public:
    void Init() {
        Mirage::ApplicationManager::GetCamera()->SetPosition(0.f, 3.f, 5.f);
        loader.loadModel("res/test.obj");

        terrain1 = new Terrain(0, 0);
        terrain2 = new Terrain(0, 1);
    }
    void Shutdown() {

    }
    void Update() {
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
};

Mirage::WindowConfig Mirage::GetConfiguration()
{
    WindowConfig config("SANDBOX", 1280, 720);
    config.initialState = []() -> Mirage::State* { return new SandboxState(); };
    return config;
}
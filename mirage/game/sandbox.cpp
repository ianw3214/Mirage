#include "engine.hpp"

#include "graphics/graphics.hpp"
#include "GL/glew.h"

class SandboxState : public Mirage::State {
public:
    void Init() {
        Mirage::ApplicationManager::GetCamera()->SetPosition(6.f, 0.f, 3.f);
        loader.loadModel("res/test.obj");
    }
    void Shutdown() {

    }
    void Update() {
        ModelRef model = loader.getModel("res/test.obj");
        model->SetPosition(0.f, 0.f, 0.f);
        model->SetScale(1.f);
        Mirage::ApplicationManager::GetRenderer()->DrawModel(model, Mirage::Colours::WHITE);
    }
private:
    OBJLoader loader;
};

Mirage::WindowConfig Mirage::GetConfiguration()
{
    WindowConfig config("SANDBOX", 1280, 720);
    config.initialState = []() -> Mirage::State* { return new SandboxState(); };
    return config;
}
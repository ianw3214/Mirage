#include "engine.hpp"

#include "mirage/graphics/graphics.hpp"
#include "GL/glew.h"

class SandboxState : public Mirage::State {
public:
    void Init() {
        loader.loadModel("res/test.obj");
    }
    void Shutdown() {

    }
    void Update() {
        ModelRef model = loader.getModel("res/test.obj");

        // TODO: Remove temporary stuff
        // RENDERING STUFF
        model->va.bind();
        model->ib.bind();
        glDrawElements(GL_TRIANGLES, model->ib.getCount(), GL_UNSIGNED_INT, nullptr);
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
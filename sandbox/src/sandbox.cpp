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

const Mirage::WindowConfig config = { "SANDBOX", 1280, 720, new SandboxState() };

class Sandbox : public Mirage::Application {
public:
    Sandbox() : Application(config) {}
    ~Sandbox() {}
private:
};

Mirage::Application * Mirage::createApplication() {
    return new Sandbox();
}
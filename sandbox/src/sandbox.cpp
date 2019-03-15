#include "engine.hpp"

const Mirage::WindowConfig config = { "SANDBOX", 1280, 720 };

class SandboxState : public Mirage::State {
public:
    void Init() {
        
    }
    void Shutdown() {

    }
    void Update() {
        
    }
private:
};

class Sandbox : public Mirage::Application {
public:
    Sandbox() : Application(config) {}
    ~Sandbox() {}
private:
};

Mirage::Application * Mirage::createApplication() {
    return new Sandbox();
}
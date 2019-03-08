#include "engine.hpp"

const Mirage::WindowConfig config = { "SANDBOX", 1280, 720 };

class Sandbox : public Mirage::Application {
public:
    Sandbox() : Application(config) {}
    ~Sandbox() {}
private:
};

Mirage::Application * Mirage::createApplication() {
    return new Sandbox();
}
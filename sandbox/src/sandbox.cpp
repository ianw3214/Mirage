#include "engine.hpp"

class Sandbox : public Mirage::Application {
public:
    Sandbox() {}
    ~Sandbox() {}
private:
};

Mirage::Application * Mirage::createApplication() {
    return new Sandbox();
}
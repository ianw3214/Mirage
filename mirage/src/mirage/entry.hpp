#pragma once

#include "application.hpp"

#ifdef PLATFORM_WINDOWS
extern Mirage::Application * Mirage::createApplication();
int main(int argc, char* argv[]) {
    Mirage::Application * app = Mirage::createApplication();
    app->Run();
    delete app;
    return 0;
}
#endif
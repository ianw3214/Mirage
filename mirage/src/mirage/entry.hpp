#pragma once

#include "application.hpp"

#include <stdexcept>

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
extern Mirage::Application * Mirage::createApplication();
INT __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
    Mirage::Application * app = Mirage::createApplication();
    app->Run();
    delete app;
    return 0;
}
#endif
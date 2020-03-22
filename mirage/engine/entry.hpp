#pragma once

#include "application.hpp"

#include <stdexcept>

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
extern Mirage::WindowConfig Mirage::GetConfiguration();
INT __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow) {
    Mirage::Application * app = new Mirage::Application(Mirage::GetConfiguration());
    app->Run();
    delete app;
    return 0;
}
#endif
#pragma once

// TODO: (Ian) Precompiled headers?

#include "util/util.hpp"

#include <string>
#include <functional>

namespace Mirage {
    class State;

    struct WindowConfig {
        std::string name;
        unsigned int width;
        unsigned int height;
        std::function<Mirage::State*()> initialState;

        WindowConfig(const std::string& name = "MIRAGE",
            unsigned int width = 500,
            unsigned int height = 500)
            : name(name), width(width), height(height)
        {

        } 
    };

    class Window {
    public:
        Window();
        ~Window();

        void Create(const WindowConfig& config = WindowConfig());

        void Update();
        void SwapBuffer();
    private:
        struct Impl;
        Impl * impl;
    };

}
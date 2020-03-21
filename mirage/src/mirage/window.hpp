#pragma once

// TODO: (Ian) Use smart pointers
// TODO: (Ian) Precompiled headers?

#include "core.hpp"

#include <string>

namespace Mirage {
    class State;

    struct WindowConfig {
        std::string name;
        unsigned int width;
        unsigned int height;
        State * initialState;

        WindowConfig(const std::string& name = "MIRAGE",
            unsigned int width = 500,
            unsigned int height = 500,
            State * initialState = nullptr)
            : name(name), width(width), height(height), initialState(initialState)
        {

        } 
    };

    class MIRAGE_API Window {
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
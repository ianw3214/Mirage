#pragma once

// TODO: (Ian) Use smart pointers
// TODO: (Ian) Precompiled headers?

#include "core.hpp"

#include <string>

struct Input;

namespace Mirage {

    struct WindowConfig {
        std::string name;
        unsigned int width;
        unsigned int height;

        WindowConfig(const std::string& name = "MIRAGE",
            unsigned int width = 500,
            unsigned int height = 500)
            : name(name), width(width), height(height)
        {

        } 
    };

    class MIRAGE_API Window {
    public:
        Window();
        ~Window();

        void Create(const WindowConfig& config = WindowConfig());

        void Update(Input * input);
    private:
        struct Impl;
        Impl * impl;
    };

}
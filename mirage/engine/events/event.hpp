#pragma once

#include "util/util.hpp"

namespace Mirage{
    class Input {
    public:
        Input();
        ~Input();
        void Update();

        // Window events
        bool WindowClosed();

        // Mouse events
        bool LeftMouseClicked();
        bool LeftMouseReleased();
        float GetMouseX() const;
        float GetMouseY() const;

        // Key events
        bool KeyPressed(int keycode);

    private:
        struct Impl;
        Impl * impl;
    };
}
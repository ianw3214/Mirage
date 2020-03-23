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

        // Key events
        bool KeyPressed(int keycode);

    private:
        struct Impl;
        Owned<Impl> impl;
    };
}
#pragma once

#include "mirage/core.hpp"
#include "mirage/util/util.hpp"

namespace Mirage{
    class MIRAGE_API Input {
    public:
        Input();
        ~Input();
        void Update();

        // Window events
        inline bool WindowClosed();

        // Mouse events
        inline bool LeftMouseClicked();
        inline bool LeftMouseReleased();

        // Key events
        inline bool KeyPressed(int keycode);

    private:
        struct Impl;
        Owned<Impl> impl;
    };
}
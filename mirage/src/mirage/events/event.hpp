#pragma once

#include "mirage/core.hpp"

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

    private:
        // TODO: (Ian) Use smart pointer
        struct Impl;
        Impl * impl;
    };
}
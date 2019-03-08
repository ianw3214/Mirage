#pragma once

#include "core.hpp"

namespace Mirage{
    class MIRAGE_API State {
    public:
        State() {}
        virtual ~State() {}

        virtual void Init() {}
        virtual void Shutdown() {}

        virtual void Update() {}
    };
}
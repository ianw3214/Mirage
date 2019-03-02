#pragma once

#include "core.hpp"

namespace Mirage {
    class API Application {
    public:
        Application();
        virtual ~Application();

        void Run();
    };

    Application * createApplication();
}
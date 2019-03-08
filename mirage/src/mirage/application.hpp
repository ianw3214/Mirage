#pragma once

#include "core.hpp"
#include "window.hpp"
#include "events/event.hpp"

namespace Mirage {

    class MIRAGE_API Application {
    public:
        Application();
        Application(const WindowConfig& config);
        virtual ~Application();

        void Run();
    protected:
        bool m_running;

        // TODO: (Ian) Use a smart pointer
        Window * m_window;
        Input * m_input;

        // Allow applications to inject their own window close behaviour
        virtual void WindowCloseCallback() {}
    private:
        void WindowClose();
    };

    Application * createApplication();
}
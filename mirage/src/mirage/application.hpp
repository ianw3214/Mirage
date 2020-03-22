#pragma once

#include "core.hpp"
#include "window.hpp"
#include "stateManager.hpp"
#include "graphics/renderer.hpp"
#include "events/event.hpp"

namespace Mirage {

    class MIRAGE_API Application {
    public:
        Application();
        Application(const WindowConfig& config);
        ~Application();

        void Run();
    protected:
        bool m_running;

        // TODO: (Ian) Use a smart pointer
        Window * m_window;
        StateManager * m_states;
        Renderer * m_renderer;
        Input * m_input;

    private:
        void WindowClose();

    };

    WindowConfig GetConfiguration();
}
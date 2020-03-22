#pragma once

#include "core.hpp"
#include "window.hpp"
#include "stateManager.hpp"
#include "graphics/renderer.hpp"
#include "events/event.hpp"

namespace Mirage {

    class Application;
    class MIRAGE_API ApplicationManager {
    public:
        // TODO: Add traps to make sure application exists and is not nullptr
        static void SetApplication(Application * application) { s_application = application; }
        static Renderer * GetRenderer();
    private:
        static Application * s_application;
    };

    class MIRAGE_API Application {
        friend class ApplicationManager;
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
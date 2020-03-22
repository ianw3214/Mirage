#pragma once

#include "core.hpp"
#include "window.hpp"
#include "stateManager.hpp"
#include "graphics/renderer.hpp"
#include "events/event.hpp"
#include "util/util.hpp"

namespace Mirage {

    //////////////////////////////////////////////////////////////////////////
    class Application;
    class MIRAGE_API ApplicationManager {
    public:
        static void SetApplication(Reference<Application> application) { s_application = application; }
        static Reference<Renderer> GetRenderer();
    private:
        static Reference<Application> s_application;
    };

    //////////////////////////////////////////////////////////////////////////
    class MIRAGE_API Application {
        friend class ApplicationManager;
    public:
        Application();
        Application(const WindowConfig& config);
        ~Application();

        void Run();
    protected:
        bool m_running;

        Owned<Window> m_window;
        Owned<StateManager> m_states;
        Owned<Renderer> m_renderer;
        Owned<Input> m_input;

    private:
        void WindowClose();

    };

    WindowConfig GetConfiguration();
}
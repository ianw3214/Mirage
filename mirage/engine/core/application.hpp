#pragma once

#include "window.hpp"
#include "stateManager.hpp"
#include "graphics/renderer.hpp"
#include "events/event.hpp"
#include "util/util.hpp"

// TODO: Put this in a 'scene' class maybe
#include "graphics/camera.hpp"

namespace Mirage {

    //////////////////////////////////////////////////////////////////////////
    class Application;
    class ApplicationManager {
    public:
        static void SetApplication(Reference<Application> application) { s_application = application; }
        static Reference<Renderer> GetRenderer();
        // TODO: Put this in a 'scene' class maybe
        static Reference<Camera> GetCamera();
    private:
        static Reference<Application> s_application;
    };

    //////////////////////////////////////////////////////////////////////////
    class Application {
        friend class ApplicationManager;
    public:
        Application();
        Application(const WindowConfig& config);
        ~Application();

        void Run();
    protected:
        bool m_running;

        Window * m_window;
        StateManager * m_states;
        Renderer * m_renderer;
        Input * m_input;

        // TODO: Put this in a 'scene' class maybe
        Camera * m_camera;

    private:
        void WindowClose();

    };

    WindowConfig GetConfiguration();
}
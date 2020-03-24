#include "application.hpp"

#include "GL/glew.h"

using namespace Mirage;

//////////////////////////////////////////////////////////////////////////
Reference<Application> ApplicationManager::s_application = nullptr;

Reference<Renderer> ApplicationManager::GetRenderer()
{
    MIRAGE_TRAP(s_application);
    return s_application->m_renderer;
}

Reference<Camera> ApplicationManager::GetCamera()
{
    MIRAGE_TRAP(s_application);
    return s_application->m_camera;
}

//////////////////////////////////////////////////////////////////////////
Application::Application() : m_running(true) {
    m_window = new Window();
    m_window->Create();

    m_states = new StateManager();

    m_input = new Input();

    ApplicationManager::SetApplication(this);
}

Application::Application(const WindowConfig& config) {
    m_window = new Window();
    m_window->Create(config);

    m_states = new StateManager();

    m_renderer = new Renderer();
    m_input = new Input();

    m_camera = new Camera();

    ApplicationManager::SetApplication(this);

    // TODO: Perhaps there can be a separate init for core systems vs gameplay systems
    m_states->PushState(config.initialState());

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}

Application::~Application() {
    // Setting to nullptr will call the destructors
    // TODO: Actually add a destroy function in smart pointers
    m_input = nullptr;
    m_states = nullptr;
    m_window = nullptr;
}

void Application::Run() {
    while(m_running) {
        m_renderer->Clear(0.f, 0.f, 0.f);

        m_window->Update();
        m_input->Update();
        m_states->Update();

        if (m_input->WindowClosed()) {
            WindowClose();
        }

        m_window->SwapBuffer();
    }
}

void Application::WindowClose() {
    m_running = false;
}
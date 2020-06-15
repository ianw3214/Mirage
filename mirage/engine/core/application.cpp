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

Reference<Input> ApplicationManager::GetInput()
{
    MIRAGE_TRAP(s_application);
    return s_application->m_input;
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
}

Application::~Application() {
    // Setting to nullptr will call the destructors
    delete m_input;
    delete m_states;
    delete m_window;

    // TODO: This will be moved when scene class implemented
    delete m_camera;
}

void Application::Run() {
    while(m_running) {
        m_renderer->Clear();

        m_input->Update();
        m_window->StartFrame();
        m_states->Update();
        m_window->EndFrame();

        if (m_input->WindowClosed()) {
            WindowClose();
        }

        m_window->SwapBuffer();
    }
}

void Application::WindowClose() {
    m_running = false;
}
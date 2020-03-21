#include "application.hpp"

#include "GL/glew.h"

using namespace Mirage;

Application::Application() : m_running(true) {
    m_window = new Window();
    m_window->Create();

    m_states = new StateManager();

    m_input = new Input();
}

Application::Application(const WindowConfig& config) {
    m_window = new Window();
    m_window->Create(config);

    m_states = new StateManager();

    m_renderer = new Renderer();
    m_input = new Input();

    m_states->PushState(config.initialState());
}

Application::~Application() {
    delete m_input;
    delete m_states;
    delete m_window;
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
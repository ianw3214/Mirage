#include "application.hpp"

using namespace Mirage;

Application::Application() : m_running(true) {
    m_window = new Window();
    m_window->Create();

    m_input = new Input();
}

Application::Application(const WindowConfig& config) {
    m_window = new Window();
    m_window->Create(config);

    m_input = new Input();
}

Application::~Application() {

}

void Application::Run() {
    while(m_running) {
        m_window->Update();
        m_input->Update();

        if (m_input->WindowClosed()) {
            WindowClose();
        }
    }
}

void Application::WindowClose() {
    WindowCloseCallback();
    m_running = false;
}
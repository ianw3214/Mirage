#include "application.hpp"

using namespace Mirage;

Application::Application() : m_running(true) {
    m_window = new Window();
    m_window->Create();

    m_input = new Input();
}

Application::~Application() {

}

void Application::Run() {
    while(m_running) {
        m_input->clear();
        m_window->Update(m_input);

        if (m_input->windowClosed) {
            WindowClose();
        }
    }
}

void Application::WindowClose() {
    WindowCloseCallback();
    m_running = false;
}
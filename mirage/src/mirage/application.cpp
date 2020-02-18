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

    // RENDERING STUFF
    glGenVertexArrays(1, &m_vertexArray);
    glBindVertexArray(m_vertexArray);

    glGenBuffers(1, &m_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArray);

    float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    glGenBuffers(1, &m_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);

    unsigned int indices[3] = {0, 1, 2};
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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

        glBindVertexArray(m_vertexArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

        if (m_input->WindowClosed()) {
            WindowClose();
        }

        m_window->SwapBuffer();
    }
}

void Application::WindowClose() {
    WindowCloseCallback();
    m_running = false;
}
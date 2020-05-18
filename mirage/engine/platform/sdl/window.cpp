#include "core/window.hpp"

// TODO: (Ian) Log errors before crashing

#include <SDL2/SDL.h>
#include <imgui.h>

#include "imgui/imgui_impl_sdl.h"

#ifdef MIRAGE_OPENGL
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>
#include "platform/opengl/imgui/imgui_impl_opengl3.h"
#endif

#include "events/event.hpp"

using namespace Mirage;
static bool s_SDL_init = false;

struct Window::Impl {
    SDL_Window * window;
    SDL_GLContext context;
};

Window::Window() {
    if (!s_SDL_init) {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            exit(1);
        }
        #ifdef MIRAGE_OPENGL
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        #endif
        s_SDL_init = true;
    }
    m_impl = new Impl();
}

Window::~Window() {
    delete m_impl;
}

// Allow configurable to eventually load in from file maybe
void Window::Create(const WindowConfig& config) {
    #ifdef MIRAGE_OPENGL
    m_impl->window = SDL_CreateWindow(config.name.c_str(), 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        config.width, 
        config.height, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (m_impl->window == nullptr) {
        exit(1);
    }
    m_impl->context = SDL_GL_CreateContext(m_impl->window);
    if (m_impl->context == NULL) {
        exit(1);
    }

    // Glew can only be initialized after a valid openGL context is created
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        exit(1);
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    const char* glsl_version = "#version 330";
    ImGui_ImplSDL2_InitForOpenGL(m_impl->window, m_impl->context);
    ImGui_ImplOpenGL3_Init(glsl_version);
    #endif
}

void Window::StartFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(m_impl->window);
    ImGui::NewFrame();

    // ImGui::ShowDemoWindow();
}

void Window::EndFrame() {
    // Rendering
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::SwapBuffer() {
    SDL_GL_SwapWindow(m_impl->window);
}
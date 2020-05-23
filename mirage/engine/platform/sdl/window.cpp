#include "core/window.hpp"

// TODO: (Ian) Log errors before crashing

#include <SDL2/SDL.h>

#ifdef MIRAGE_EDITOR
#include <imgui-docking/imgui.h>
#include "imgui/imgui_impl_sdl.h"
#endif

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

    #ifdef MIRAGE_EDITOR
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer bindings
    const char* glsl_version = "#version 330";
    ImGui_ImplSDL2_InitForOpenGL(m_impl->window, m_impl->context);
    ImGui_ImplOpenGL3_Init(glsl_version);
    #endif
    #endif
}

void Window::StartFrame() {
    #ifdef MIRAGE_EDITOR
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(m_impl->window);
    ImGui::NewFrame();

    {   // Docking windows
        ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        dockspace_flags ^= ImGuiDockNodeFlags_NoDockingInCentralNode;
        dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode;
        dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar;

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->GetWorkPos());
        ImGui::SetNextWindowSize(viewport->GetWorkSize());
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", nullptr, window_flags);
        ImGui::PopStyleVar();

        ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }
        ImGui::End();
    }

    {   // Base engine debug window
        static bool sRenderWireframe = false;

        ImGui::Begin("Engine");
        // ImGui::SameLine();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Checkbox("Wireframe render mode", &sRenderWireframe);
        ImGui::End();

        glPolygonMode(GL_FRONT_AND_BACK, sRenderWireframe ? GL_LINE : GL_FILL);
    }
    #endif
}

void Window::EndFrame() {
    #ifdef MIRAGE_EDITOR
    // Rendering
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::Render();
    glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    // Update and Render additional Platform Windows
    // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
    //  For this specific demo app we could also call SDL_GL_MakeCurrent(window, gl_context) directly)
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
        SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
    }
    #endif
}

void Window::SwapBuffer() {
    SDL_GL_SwapWindow(m_impl->window);
}
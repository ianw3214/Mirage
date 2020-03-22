#include "window.hpp"

// TODO: (Ian) Log errors before crashing
// TODO: (Ian) Use WIN32 API to handle low level systems

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

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
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
        s_SDL_init = true;
    }
    impl = new Impl();
}

Window::~Window() {
    
}

// Allow configurable to eventually load in from file maybe
void Window::Create(const WindowConfig& config) {
    impl->window = SDL_CreateWindow(config.name.c_str(), 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED, 
        config.width, 
        config.height, 
        SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
    if (impl->window == nullptr) {
        exit(1);
    }
    impl->context = SDL_GL_CreateContext(impl->window);
    if (impl->context == NULL) {
        exit(1);
    }

    // Glew can only be initialized after a valid openGL context is created
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        exit(1);
    }
}

void Window::Update() {

}

void Window::SwapBuffer() {
    SDL_GL_SwapWindow(impl->window);
}
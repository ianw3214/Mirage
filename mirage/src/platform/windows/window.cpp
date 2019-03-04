#include "mirage/window.hpp"

// TODO: (Ian) Use WIN32 API to handle low level systems
#include <SDL2/SDL.h>

// TODO: (Ian) Probably don't want to use exceptions
#include <stdexcept>

#include "mirage/events/event.hpp"

using namespace Mirage;
static bool s_SDL_init = false;

struct Window::Impl {
    SDL_Window * window;
};

Window::Window() {
    if (!s_SDL_init) {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
            throw new std::runtime_error("SDL Failed to initialize");
        }
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
        SDL_WINDOW_SHOWN);
}

void Window::Update(Input * input) {
    // Poll events on the update
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if (e.type == SDL_WINDOWEVENT_CLOSE || e.type == SDL_QUIT) {
            input->windowClosed = true;
        }
    }
}
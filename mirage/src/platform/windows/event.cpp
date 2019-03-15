#include "mirage/events/event.hpp"

#include <SDL2/SDL.h>

struct Mirage::Input::Impl {
    // Window event variables
    bool windowClosed;

    // Mouse event variables
    bool leftMouseClicked;
    bool leftMouseReleased;

    Impl() : windowClosed(false), leftMouseClicked(false), leftMouseReleased(false) {}
    void Clear() {
        windowClosed = false;
        leftMouseClicked = false;
        leftMouseReleased = false;
    }
};

Mirage::Input::Input() {
    impl = new Impl();
}
Mirage::Input::~Input() {
    delete impl;
}

void Mirage::Input::Update() {
    // Clear the previous input state first
    impl->Clear();
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        // TODO: (Ian) Also check for SDL_WINDOWEVENT_CLOSE
        if (e.type == SDL_QUIT) {
            impl->windowClosed = true;
        }
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            impl->leftMouseClicked = true;
        }
        if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
            impl->leftMouseReleased = true;
        }
    }
}

bool Mirage::Input::WindowClosed() {
    return impl->windowClosed;
}

bool Mirage::Input::LeftMouseClicked() {
    return impl->leftMouseClicked;
}

bool Mirage::Input::LeftMouseReleased() {
    return impl->leftMouseReleased;
}

bool Mirage::Input::KeyPressed(int keycode) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    return state[keycode];   
}
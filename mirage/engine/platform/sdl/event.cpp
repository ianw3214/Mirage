#include "events/event.hpp"

#include <SDL2/SDL.h>

#include "imgui/imgui_impl_sdl.h"

struct Mirage::Input::Impl {
    // Window event variables
    bool windowClosed;

    // Mouse event variables
    bool leftMouseClicked;
    bool leftMouseReleased;
    int mouseX;
    int mouseY;

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
        if (e.type == SDL_QUIT || (e.type == SDL_WINDOWEVENT && e.window.event == SDL_WINDOWEVENT_CLOSE)) {
            impl->windowClosed = true;
        }
        #ifdef MIRAGE_EDITOR
        ImGui_ImplSDL2_ProcessEvent(&e);
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        if (!io.WantCaptureMouse)
        {
            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                impl->leftMouseClicked = true;
            }
            if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
                impl->leftMouseReleased = true;
            }
        }
        if (!io.WantCaptureKeyboard)
        {
            // TODO: Implement
        }
        #else
        if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
            impl->leftMouseClicked = true;
        }
        if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) {
            impl->leftMouseReleased = true;
        }
        #endif
    }
    SDL_GetMouseState(&(impl->mouseX), &(impl->mouseY));
    // SDL 
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

float Mirage::Input::GetMouseX() const
{
    return static_cast<float>(impl->mouseX);
}

float Mirage::Input::GetMouseY() const
{
    return static_cast<float>(impl->mouseY);
}

bool Mirage::Input::KeyPressed(int keycode) {
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    return state[keycode];   
}
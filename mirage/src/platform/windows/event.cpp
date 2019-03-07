#include "mirage/events/event.hpp"

#include <SDL2/SDL.h>

bool Input::KeyPressed(int key) const {
    const Uint8 * keys = SDL_GetKeyboardState(NULL);
    return keys[key];
}
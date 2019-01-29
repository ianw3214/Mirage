#define SDL_MAIN_HANDLED

#include "engine/engine.hpp"

int main(int argc, char* argv[]) {

    // Initilaize everything
    Engine::init();

    // Initialize to first state of the game
    Engine::setState(new State());

    // Run the game engine
    Engine::run();

    return 0;

}
/* 
 *  The static class containing the main engine code 
 */
#pragma once

#include <SDL2/SDL.h>

class ResourceManager;
class Renderer;
class ImGuiWrapper;

class State {
public:
    void init();
    void shutdown();
    void update();
    void render();
private:
};

class Engine {
public:
    static void init();
    static void shutdown();
    static void setState(State * state);
    static void run();

    static SDL_Window * getWindow();

    static ResourceManager* getResource();
    static Renderer* getRenderer();
private:
    static SDL_Window* s_window;
    static SDL_GLContext s_context;

    static State * s_state;

    // Subsystems
    static ResourceManager* s_resourceManager;
    static Renderer * s_renderer;
    static ImGuiWrapper * s_ImGui;
};
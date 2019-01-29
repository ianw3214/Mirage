#include "engine.hpp"

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "resource.hpp"
#include "renderer.hpp"
#include "imgui_wrapper.hpp"

// Includes for the sample state
#include "opengl/shader.hpp"
#include "obj.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

// glm::mat4 proj = glm::perspective(glm::radians(30.f), 1.f, 0.1f, 100.0f);
glm::mat4 proj = glm::ortho(-10.f, 10.f, -10.f, 10.f, -1000.f, 1000.f);
// View matrix construction
glm::mat4 view = glm::lookAt(glm::vec3(20.f, 20.f, 0.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
glm::mat4 model = glm::mat4(1.0f);

void State::init() {
    // Do nothing...
}
void State::shutdown() {
    // Do nothing...
}
void State::update() {
    // Do nothing...
}
void State::render() {
    ShaderRefPtr shader = Engine::getResource()->getShader("default2D");
    if (shader) {
        Engine::getRenderer()->drawLine(100, 100, 200, 200, shader.get());
    }
    static RawModel mod;
    if (!mod.va) mod.loadModel("res/models/wedge.obj");
    // Model view projection matrix construction
	glm::mat4 mvp = proj * view * model;
    ShaderRefPtr shader3d = Engine::getResource()->getShader("default3D");
    if (shader3d) {
        shader3d->setUniformMat4f("u_MVP", mvp);
        Engine::getRenderer()->drawTriangles(*(mod.va), *(mod.ib), *shader3d);
    }
}

SDL_Window*         Engine::s_window;
SDL_GLContext       Engine:: s_context;
State*              Engine::s_state;
ResourceManager*    Engine::s_resourceManager;
Renderer *          Engine::s_renderer;
ImGuiWrapper *      Engine::s_ImGui;

void Engine::init() {
    // Just crash the game if things fail
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        exit(1);
    }

    // Set openGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    // Create SDL window
    // TODO: (Ian) Load in properties from a config file
    s_window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 500, SDL_WINDOW_OPENGL);
    if (s_window == NULL) {
        exit(1);
    }

    // Create the OpenGL context
    s_context = SDL_GL_CreateContext(s_window);
    if (s_context == NULL) {
        exit(1);
    }

    // Enable vsync
    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        // glewGetErrorString(glewError);
        exit(1);
    }

    // Set the clear colour to black
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // Allocate/initialize subsystems
    s_renderer = new Renderer;
    s_resourceManager = new ResourceManager;
    s_ImGui = new ImGuiWrapper;

    // TODO: (Ian) Move this to init function of the resource manager
    // Load default resources
    ShaderRefPtr default_shader = Engine::getResource()->loadShader("default2D", VERTEX_2D_PATH, FRAG_PATH);
    default_shader->setUniform1i("u_screen_width", 500);
    default_shader->setUniform1i("u_screen_height", 500);
    ShaderRefPtr default_shader_3D = Engine::getResource()->loadShader("default3D", VERTEX_3D_PATH, FRAG_PATH);

}
void Engine::shutdown() {
    // Not actually too important, OS will take care of it
    SDL_Quit();
}
void Engine::setState(State * state) {
    if (s_state) {
        s_state->shutdown();
    }
    delete s_state;
    s_state = state;
    if (s_state) {
        s_state->init();
    }
}
void Engine::run() {
    bool running = true;
    while (running) {

        // Clear the screen colour
        glClear(GL_COLOR_BUFFER_BIT);

        // TODO: (Ian) Use custom event struct/class
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }
            if (e.type == SDL_QUIT) {
                running = false;
            }
            // Call event handler of other shit
            s_ImGui->onEvent(e);
        }

        // Update the state
        s_state->update();
        s_state->render();

        // Render ImGui
        s_ImGui->render();

        SDL_GL_SwapWindow(s_window);
    }
}

SDL_Window * Engine::getWindow() {
    return s_window;
}

ResourceManager* Engine::getResource() {
    return s_resourceManager;
}

Renderer* Engine::getRenderer() {
    return s_renderer;
}
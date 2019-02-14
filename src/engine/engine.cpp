#include "engine.hpp"

#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include "resource.hpp"
#include "graphics/renderer.hpp"
#include "ImGui/imgui_wrapper.hpp"

// Includes for the sample state
#include "platform/opengl/shader.hpp"
#include "platform/openGL/glwrappers.hpp"
#include "graphics/rawModel.hpp"
#include "glm/gtc/matrix_transform.hpp"

// Textures
Texture * texture;

void State::init() {
    // Initialize the lighitng shader
    Engine::getRenderer()->setClearColour(.7f, .7f, .9f);
    ShaderRefPtr mainShader = Engine::getResource()->loadShader("lighting", "res/shaders/default3d.vert", "res/shaders/lighting_texture.frag");
    mainShader->setUniform3f("sunColour", .8f, .7f, .5f);
    mainShader->setUniform3f("sunDir", 0.f, -1.f, 0.f);
    ShaderRefPtr lightShader = Engine::getResource()->loadShader("lighting2", "res/shaders/default3d.vert", "res/shaders/lighting.frag");
    lightShader->setUniform3f("sunColour", .8f, .7f, .5f);
    lightShader->setUniform3f("sunDir", 0.f, -1.f, 0.f);
    lightShader->setUniform3f("objectColour", 1.f, 0.f, 0.f);

    // Temporary camera setting code
    camera.setPosition(0.f, 1.f, 0.f);
    camera.setDirection(1.f, 0.f, 0.f);
    // camera.setDefaultMovement(false);

    // Initialize terrain shit
    terrain.reserve(4);
    terrain.emplace_back(0.f, 0.f);
    terrain.emplace_back(-1.f, 0.f);
    terrain.emplace_back(0.f, -1.f);
    terrain.emplace_back(-1.f, -1.f);
    texture = new Texture("res/textures/grass.png");

    // Temporary player initialization code
    player.loadModel("res/player.obj");
}
void State::shutdown() {
    // Do nothing...
}
void State::onEvent(const SDL_Event& e) {
    camera.onEvent(e);
}
void State::update() {
    camera.update();
}
void State::render() {

    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 proj = glm::perspective(glm::radians(camera.getFov()), 1280.f / 720.f, 0.1f, 1000.f);

    /*  LINE RENDERING
    ShaderRefPtr shader = Engine::getResource()->getShader("default2D");
    if (shader) {
        Engine::getRenderer()->drawLine(100, 100, 200, 200, shader.get());
    }
    */

    // Model view projection matrix construction
    ShaderRefPtr shader3d = Engine::getResource()->getShader("lighting");
    if (shader3d) {
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 mvp = proj * view * model;
        texture->bind();
        // Set textures to repeat
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        shader3d->setUniformMat4f("u_MVP", mvp);
        /*
        shader3d->setUniform3f("lightColour", 1.f, 1.f, 1.f);
        shader3d->setUniform3f("objectColour", 0.f, 0.f, 1.f);
        shader3d->setUniform3f("lightPos", 3.f, 1.f, 0.f);
        */
        shader3d->setUniformMat4f("u_model", model);
        // Render the terrain
        for (const Terrain& t : terrain) {
            Engine::getRenderer()->drawTriangles(*(t.getModel().va), *(t.getModel().ib), *shader3d);
        }
        texture->unbind();
    }
    // Render the player
    ShaderRefPtr shader3d2 = Engine::getResource()->getShader("lighting2");
    if (shader3d2) {
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(1.f, 2.f, 1.f));
        glm::mat4 mvp = proj * view * model;
        shader3d2->setUniformMat4f("u_MVP", mvp);
        /*
        shader3d2->setUniform3f("lightColour", 0.f, 0.f, 0.f);
        shader3d2->setUniform3f("objectColour", 0.f, 0.f, 1.f);
        shader3d2->setUniform3f("lightPos", 3.f, 1.f, 0.f);
        */
        shader3d2->setUniformMat4f("u_model", model);
        Engine::getRenderer()->drawTriangles(*(player.va), *(player.ib), *shader3d2);
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
    s_window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, SDL_WINDOW_OPENGL);
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
    // Enable mouse trapping
    SDL_SetRelativeMouseMode(SDL_TRUE);
    
    // Wireframe mode
    // TODO: (Ian) Set this as an option or some shit
    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

    // Initialize OpenGL properties
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glCullFace(GL_BACK);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    GLenum glewError = glewInit();
    if (glewError != GLEW_OK) {
        // glewGetErrorString(glewError);
        exit(1);
    }

    // Set the clear colour to black
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // Allocate/initialize subsystems
    s_renderer = new Renderer();
    s_resourceManager = new ResourceManager;
    s_ImGui = new ImGuiWrapper;

    // Load default resources
    ShaderRefPtr default_shader = Engine::getResource()->loadShader("default2D", VERTEX_2D_PATH, FRAG_PATH);
    default_shader->setUniform1i("u_screen_width", 500);
    default_shader->setUniform1i("u_screen_height", 500);
    ShaderRefPtr default_shader_3D = Engine::getResource()->loadShader("default3D", VERTEX_3D_PATH, FRAG_PATH);
    s_renderer->setDefault(default_shader.get(), default_shader_3D.get());

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
            s_state->onEvent(e);
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
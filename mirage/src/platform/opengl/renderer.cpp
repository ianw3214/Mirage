#include "mirage/renderer.hpp"
using namespace Mirage;

#include <GL/glew.h>

#include "shader.hpp"

struct Renderer::Impl {
    Shader * m_basicShader;
};

Renderer::Renderer()
{
    m_impl = new Renderer::Impl();
    m_impl->m_basicShader = new Shader("res/shaders/vert.glsl", "res/shaders/frag.glsl");
    m_impl->m_basicShader->setUniform4f("u_Colour", 1.f, 0.f, 1.f, 1.f);
}

void Renderer::Clear(float r, float g, float b)
{
    glClearColor(r, g, b, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}
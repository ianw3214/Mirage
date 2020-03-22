#include "graphics/renderer.hpp"
using namespace Mirage;

#include <GL/glew.h>

#include "shader.hpp"

struct Renderer::Impl {
    Shader * m_basicShader;
    Shader * m_transformShader;
};

Renderer::Renderer()
{
    m_impl = new Renderer::Impl();
    m_impl->m_basicShader = new Shader("res/shaders/vert.glsl", "res/shaders/frag.glsl");
    m_impl->m_basicShader->setUniform4f("u_Colour", 1.f, 0.f, 1.f, 1.f);
    m_impl->m_transformShader = new Shader("res/shaders/transform.glsl", "res/shaders/frag.glsl");
    m_impl->m_transformShader->setUniform4f("u_Colour", 1.f, 0.f, 1.f, 1.f);
}

void Renderer::Clear(float r, float g, float b)
{
    glClearColor(r, g, b, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);
}

const unsigned int SQUARE_INDICES[6] = { 0, 1, 3, 0, 2, 3 };
void Renderer::DrawQuad(float x, float y, float w, float h, const Colour& colour)
{
    // TODO: Store buffers somewhere and adjust unfiforms to draw
    float positions[8] = {
        x, y,
        x, y + h,
        x + w, y,
        x + w, y + h
    };
	VertexArray		va;
	VertexBuffer	vb(positions, sizeof(float) * 8);
	IndexBuffer		ib(SQUARE_INDICES, 6);
	// Specify the layout of the buffer data
	VertexBufferLayout layout;
	layout.pushFloat(2);
	va.addBuffer(vb, layout);

	// Issue the actual draw call
    m_impl->m_basicShader->setUniform4f("u_Colour", colour.r, colour.g, colour.b, 1.f);
	m_impl->m_basicShader->bind();
	va.bind();
	ib.bind();

	glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::DrawModel(ModelRef model, const Colour& colour)
{
    m_impl->m_basicShader->setUniform4f("u_Colour", colour.r, colour.g, colour.b, 1.f);
    m_impl->m_basicShader->bind();

    model->va.bind();
    model->ib.bind();
    glDrawElements(GL_TRIANGLES, model->ib.getCount(), GL_UNSIGNED_INT, nullptr);
}
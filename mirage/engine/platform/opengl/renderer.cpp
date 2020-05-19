#include "graphics/renderer.hpp"
using namespace Mirage;

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "core/application.hpp"
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

    // glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnable(GL_DEPTH_TEST);
}

void Renderer::Clear(float r, float g, float b)
{
    glClearColor(r, g, b, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

void Renderer::DrawModel(ModelRef modelRef, const Colour& colour)
{
    Reference<Camera> camera = ApplicationManager::GetCamera();

    glm::mat4 model = glm::mat4(1.f);
    // column major so we translate first
    model = glm::translate(model, modelRef->GetPosition().Get());
    // TODO: Implement rotate
    // model = glm::rotate(model, angle, glm::vec3(0.f, 0.f, 1.f));
    model = glm::scale(model, glm::vec3(modelRef->GetScale()));
    // glm::mat4 projection = glm::ortho(-8.f, 8.f, -6.f, 6.f, -10.f, 100.f);
    glm::mat4 view = camera->GetViewMatrix();
    glm::mat4 projection = camera->GetProjectionMatrix();

    m_impl->m_transformShader->setUniformMat4("model", glm::value_ptr(model));
    m_impl->m_transformShader->setUniformMat4("view", glm::value_ptr(view));
    m_impl->m_transformShader->setUniformMat4("projection", glm::value_ptr(projection));
    m_impl->m_transformShader->setUniform3f("u_Camera", camera->GetX(), camera->GetY(), camera->GetZ());
    m_impl->m_transformShader->setUniform4f("u_Colour", colour.r, colour.g, colour.b, 1.f);
    m_impl->m_transformShader->bind();

    modelRef->va.bind();
    modelRef->ib.bind();
    glDrawElements(GL_TRIANGLES, modelRef->ib.getCount(), GL_UNSIGNED_INT, nullptr);
}
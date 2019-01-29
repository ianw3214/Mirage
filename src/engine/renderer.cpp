#include "renderer.hpp"

// Index orders for different shapes
const unsigned int LINE_INDICES[2] = { 0, 1 };

Renderer::Renderer() : default2d(VERTEX_2D_PATH, FRAG_PATH), default3d(VERTEX_3D_PATH, FRAG_PATH) {
}

// TODO: (Ian) Temporary, remove(move) these functions
float lerp(float min, float max, float val) {
    return min + (max - min) * val;
}

void Renderer::clear() const {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::drawLine(int x1, int y1, int x2, int y2, const Shader * const shader) const {
	int positions[4] = { x1, y1, x2, y2 };
	VertexArray		va;
	VertexBuffer	vb(positions, sizeof(float) * 4);
	IndexBuffer		ib(LINE_INDICES, 2);
	// Specify the layout of the buffer data
	VertexBufferLayout layout;
	layout.push_int(2);
	va.addBuffer(vb, layout);

	if(shader) 	drawLines(va, ib, *shader);
	else 		drawLines(va, ib, default2d);
}

void Renderer::drawTriangles(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const {
	draw(va, ib, shader, GL_TRIANGLES);
}

void Renderer::drawLines(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const {
	draw(va, ib, shader, GL_LINES);
}

void Renderer::drawLineStrip(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const {
	draw(va, ib, shader, GL_LINE_STRIP);
}

void Renderer::draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader, GLenum type) const {
	shader.bind();
	va.bind();
	ib.bind();

	// Assume the buffer is always of type UINT
	glDrawElements(type, ib.getCount(), GL_UNSIGNED_INT, nullptr);
}
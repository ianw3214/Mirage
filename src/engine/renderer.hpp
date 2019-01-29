#pragma once

#include <GL/glew.h>

#include "opengl/shader.hpp"
#include "opengl/glwrappers.hpp"

#define DEFAULT_SHADER_2D	"default2d";
#define DEFAULT_SHADER_3D	"default3d";

// TODO: (Ian) Load these in from a config file
#define VERTEX_2D_PATH  "res/shaders/default2d.vert"
#define VERTEX_3D_PATH  "res/shaders/default3d.vert"
#define FRAG_PATH       "res/shaders/default.frag"

class Renderer {

public:
	Renderer();

	void clear() const;

	// Easier to use draw functions
	void drawLine(int x1, int y1, int x2, int y2, const Shader * const shader=nullptr) const;

	// Helper draw functions using OpenGL wrappers
	void drawTriangles(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void drawLines(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void drawLineStrip(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

private:
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLenum type) const;

	Shader default2d;
	Shader default3d;
};
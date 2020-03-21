#pragma once

#include "mirage/core.hpp"
#include <GL/glew.h>

class MIRAGE_API VertexBuffer {

public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind() const;
	void unBind() const;
private:
	// This represents the vertex buffer id in openGL
	GLuint bufferID;
};
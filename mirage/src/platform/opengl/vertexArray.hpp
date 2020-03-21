#pragma once

#include "mirage/core.hpp"
#include "vertexBuffer.hpp"
#include "vertexBufferLayout.hpp"

#include <GL/glew.h>

class MIRAGE_API VertexArray {

public:
	VertexArray();
	~VertexArray();

	void addBuffer(const VertexBuffer & vb, const VertexBufferLayout& layout, unsigned int index = 0);

	void bind() const;
	void unbind() const;
private:
	GLuint arrayID;
};

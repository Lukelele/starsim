#pragma once

#include <glad/glad.h>


class VertexBuffer
{
public:
	VertexBuffer(const void* bufferData, GLsizeiptr size, GLenum drawType = GL_STATIC_DRAW);
	VertexBuffer();
	~VertexBuffer();

	void AddData(const void* bufferData, GLsizeiptr size, GLenum drawType = GL_STATIC_DRAW);
	void Bind();
	void Unbind();
private:
	GLuint BufferID;
};

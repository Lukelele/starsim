#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const void* bufferData, GLsizeiptr size, GLenum drawType) {
	glGenBuffers(1, &BufferID);
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ARRAY_BUFFER, size, bufferData, drawType);
}

VertexBuffer::VertexBuffer() {
	glGenBuffers(1, &BufferID);
}

void VertexBuffer::AddData(const void* bufferData, GLsizeiptr size, GLenum drawType) {
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
	glBufferData(GL_ARRAY_BUFFER, size, bufferData, drawType);
}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &BufferID);
}

void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
}

void VertexBuffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, BufferID);
}

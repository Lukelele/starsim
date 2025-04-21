#pragma once

#include <vector>
#include <glad/glad.h>

#include "VertexBuffer.h"
#include "VertexBufferAttribute.h"

using namespace std;


class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void UnBind();
	void AddBuffer(VertexBuffer &buffer, vector<VertexBufferAttribute> &attributeVec);
	void AddBuffer(VertexBuffer& buffer, VertexBufferAttribute& attribute);
private:
	GLuint VertexArrayID;
};


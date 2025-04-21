#include "VertexArray.h"


VertexArray::VertexArray() {
	glGenVertexArrays(1, &VertexArrayID);
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &VertexArrayID);
}

void VertexArray::Bind() {
	glBindVertexArray(VertexArrayID);
}

void VertexArray::UnBind() {
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(VertexBuffer& buffer, vector<VertexBufferAttribute>& attributeVec) {
	Bind();
	buffer.Bind();

	for (int i = 0; i < attributeVec.size(); i++) {
		glEnableVertexAttribArray(attributeVec[i].index);
		glVertexAttribPointer(attributeVec[i].index, attributeVec[i].countsPerVertex, attributeVec[i].dataVariableType, attributeVec[i].normalised, attributeVec[i].stride, attributeVec[i].startPointer);
	}
}

void VertexArray::AddBuffer(VertexBuffer &buffer, VertexBufferAttribute &attribute) {
	Bind();
	buffer.Bind();

	glEnableVertexAttribArray(attribute.index);
	glVertexAttribPointer(attribute.index, attribute.countsPerVertex, attribute.dataVariableType, attribute.normalised, attribute.stride, attribute.startPointer);
}

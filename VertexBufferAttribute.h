#pragma once

struct VertexBufferAttribute
{
	VertexBufferAttribute(unsigned int attributeIndex, unsigned int attributeCountsPerVertex, unsigned int attributeDataVariableType, bool attributeNormalised, int attributeStride, void* attributeStartPointer)
		:index(attributeIndex), countsPerVertex(attributeCountsPerVertex), dataVariableType(attributeDataVariableType), normalised(attributeNormalised), stride(attributeStride), startPointer(attributeStartPointer)
	{
	}
	VertexBufferAttribute();

	unsigned int index;
	unsigned int countsPerVertex;
	unsigned int dataVariableType;
	bool normalised = 0;
	int stride = 0;
	void* startPointer = 0;
};

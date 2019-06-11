#include "VertexBuffer.h"

namespace ssfw
{
	//Draw type is either GL_STATIC_DRAW or GL_DYNAMIC_DRAW
	VertexBuffer::VertexBuffer(std::vector<float> positions, GLenum drawType)
	{
		//Vertex Buffer Setup
		glGenBuffers(1, &bufferID);
		glBufferData(GL_ARRAY_BUFFER, positions.size()*sizeof(float), positions.data(), drawType);
	}

	VertexBuffer::~VertexBuffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &bufferID);
	}

	void VertexBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, bufferID);
	}

	void VertexBuffer::update(std::vector<float> positions)
	{
		glBufferSubData(GL_ARRAY_BUFFER, 0, positions.size()*sizeof(float), positions.data());
	}
}
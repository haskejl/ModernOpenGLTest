#include "IndexBuffer.h"

namespace ssfw
{
	//drawType is either GL_STATIC_DRAW or GL_DYNAMIC_DRAW
	IndexBuffer::IndexBuffer(std::vector<unsigned int>  indices, GLenum drawType)
	{
		glGenBuffers(1, &bufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), indices.data(), drawType);
	}


	IndexBuffer::~IndexBuffer()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &bufferID);
	}

	void IndexBuffer::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
	}
}
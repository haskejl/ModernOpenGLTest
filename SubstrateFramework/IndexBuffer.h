#pragma once

#include <GL/glew.h>
#include <vector>

namespace ssfw
{
	class IndexBuffer
	{
	private:
		unsigned int bufferID;

	public:
		IndexBuffer(std::vector<unsigned int> indices, GLenum drawType);
		~IndexBuffer();

		void bind();
	};
}
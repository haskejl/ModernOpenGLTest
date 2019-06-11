#pragma once

#include <GL/glew.h>
#include <vector>

namespace ssfw
{
	class VertexBuffer
	{
	private:
		unsigned int bufferID;

	public:
		VertexBuffer(std::vector<float> positions, GLenum drawType);
		~VertexBuffer();

		void bind();
		void update(std::vector<float> positions);
	};
}
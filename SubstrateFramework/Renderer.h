#pragma once

#include "Camera.h"
#include "Shader.h"
#include "Mesh.h"

namespace ssfw
{
	class Renderer
	{
	private:
		Camera *cam;
		Mesh cube;
		uint32_t shader;
		unsigned int vertArray;

	public:
		Renderer();
		~Renderer();

		void draw();
		void moveCamera(Vec3D<float> movVec);
		void moveCamera(Mat3x3<float> rotMat);
		void moveCamera(Vec3D<float> movVec, Mat3x3<float> rotMat);
		void moveCamera(float scalar);
	};
}
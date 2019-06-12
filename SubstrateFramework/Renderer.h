#pragma once

#include "Camera.h"

namespace ssfw
{
	class Renderer
	{
	private:
		Camera *cam;
	public:
		Renderer();
		~Renderer();

		void draw();
		void moveCamera(Vec3D<float> movVec);
		void moveCamera(Mat3x3<float> rotMat);
		void moveCamera(Vec3D<float> movVec, Mat3x3<float> rotMat);
	};
}
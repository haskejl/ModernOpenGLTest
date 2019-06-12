#pragma once

#include "Math.h"

namespace ssfw
{
	class Camera
	{
	private:
		Mat4x4<float> *projMat;
		Mat4x4<float> *viewMat;
		float top, bottom, left, right, near, far;

	public:
		Camera(float topin, float bottomin, float leftin, float rightin, float nearin, float farin);
		Camera();
		~Camera();

		void setProjMat();
		void setViewMat();
		void updateViewMat(Mat4x4<float> &transMat);
	};
}
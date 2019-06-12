#include "Camera.h"

namespace ssfw
{
	Camera::Camera(float topin, float bottomin, float leftin, float rightin, float nearin, float farin)
	{
		top = topin;
		bottom = bottomin;
		left = leftin;
		right = rightin;
		near = nearin;
		far = farin;
	}

	Camera::Camera()
	{
	}

	Camera::~Camera()
	{
		delete projMat;
		delete viewMat;
	}

	void Camera::setProjMat()
	{
		float a[4][4] = 
		{
			{ ((2 * near) / (right - left)), 0.f, ((right + left) / (right - left)), 0.f },
			{ 0.f, ((2 * near) / (top - bottom)), (top + bottom) / (top - bottom), 0.f},
			{ 0.f, 0.f, -((far + near) / (far - near)), -((2 * near*far) / (far - near))},
			{ 0.f, 0.f, -1.f, 0.f}
		};
		projMat = new Mat4x4<float>(a);
	}

	//sets the default camera position and rotation to 0, 0, 0 facing down the +z axis
	void Camera::setViewMat()
	{
		viewMat = new Mat4x4<float>(Mat4x4<float>::getIdentMat());
	}

	void Camera::updateViewMat(Mat4x4<float> &transMat)
	{
		viewMat = &(*viewMat * transMat);
	}
}
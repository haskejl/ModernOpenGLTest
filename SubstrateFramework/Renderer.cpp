#include "Renderer.h"

namespace ssfw
{
	Renderer::Renderer()
	{
		cam = new Camera(0.f, 1.f, 0.f, 1.f, 0.f, 1.f);
	}

	Renderer::~Renderer()
	{
		delete cam;
	}

	void Renderer::draw()
	{
		//Apply View Matrix
		//Apply Proj Matrix
	}

	void Renderer::moveCamera(Vec3D<float> movVec)
	{
		Mat4x4<float> transMat(Mat3x3<float>::getIdentMat(), movVec);
		cam->updateViewMat(transMat);
	}
	void Renderer::moveCamera(Mat3x3<float> rotMat)
	{
		Mat4x4<float> transMat(rotMat, Vec3D<float>(0.f, 0.f, 0.f));
		cam->updateViewMat(transMat);
	}
	void Renderer::moveCamera(Vec3D<float> movVec, Mat3x3<float> rotMat)
	{
		Mat4x4<float> transMat(rotMat, movVec);
		cam->updateViewMat(transMat);
	}
}
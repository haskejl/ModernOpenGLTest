#include "Model.h"

namespace ssfw
{
	Model::Model(Mesh & meshin, Mat4x4<float>& min)
	{
		mesh = &meshin;
		toWorldMat = min;
	}
	Model::Model()
	{
	}


	Model::~Model()
	{
	}
	void Model::create(Mesh & meshin, Mat4x4<float>& min)
	{
		mesh = &meshin;
		toWorldMat = min;
	}
}
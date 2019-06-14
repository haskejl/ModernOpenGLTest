#pragma once

#include <vector>

#include "Mesh.h"
//#include "Material.h"
#include "Math.h"

namespace ssfw
{
	class Model
	{
	private:
		Mesh *m;
		Mat4x4<float> toWorldMat;
		//std::vector<Material*> mats;

	public:
		Model();
		~Model();
	};
}
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
		Mesh *mesh;
		Mat4x4<float> toWorldMat;
		//std::vector<Material*> mats;

	public:
		Model(Mesh &meshin, Mat4x4<float> &min);
		Model();
		~Model();

		void create(Mesh &meshin, Mat4x4<float> &min);
		Mesh &getMesh() { return *mesh; }
		Mat4x4<float> &getTransMat() { return toWorldMat; }
	};
}
#pragma once

#include <string>

#include "Mesh.h"

namespace ssfw
{
	//Wraps meshID and model->world matrix in a struct
	struct Model
	{
		std::string meshID;
		Mat4x4<float> toWorldMat;

		//Method to create a new mesh
		inline void create(std::string &mID, Mat4x4<float> transMat)
		{
			meshID = mID;
			toWorldMat = transMat;
		}//end void create(std::string, Mat4x4<float>)
	};// End struct Model
}
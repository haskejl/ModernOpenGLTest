#pragma once

#include <vector>

#include "IndexBuffer.h"

namespace ssfw
{
	class Material
	{
	public:
		IndexBuffer *indBuf;

		std::string matID;
		std::vector<unsigned int> indices;

		float *emission;
		float *ambient;
		float *diffuse;
		float *specular;
		float shininess;

		Material(std::string mID);
		Material(std::string mID, int ind[], float emi[], float amb[], float dif[], float spec[], float shi);
		~Material();

		void genBufs();
	};
}
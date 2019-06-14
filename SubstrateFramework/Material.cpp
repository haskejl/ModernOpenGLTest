#include "Material.h"

namespace ssfw
{
	Material::Material(std::string mID)
	{
		emission = new float[4];
		ambient = new float[4];
		diffuse = new float[4];
		specular = new float[4];

		matID = mID;
	}

	Material::Material(std::string mID, int ind[], float emi[], float amb[], float dif[], float spec[], float shi)
	{
		emission = new float[4];
		ambient = new float[4];
		diffuse = new float[4];
		specular = new float[4];

		matID = mID;
		for (int i = 0; i < 4; i++)
		{
			emission[i] = emi[i];
			ambient[i] = amb[i];
			diffuse[i] = dif[i];
			specular[i] = spec[i];
		}
		shininess = shi;
	}

	Material::~Material()
	{
		indices.~vector();
	}

	void Material::genBufs()
	{
		indBuf = new IndexBuffer(indices, GL_STATIC_DRAW);
	}
}
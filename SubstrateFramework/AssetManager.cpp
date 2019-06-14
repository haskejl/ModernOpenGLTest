#include "AssetManager.h"

namespace ssfw
{
	AssetManager::AssetManager()
	{
		meshTransMatCount = 0;
		meshCount = 0;
		meshIterCounter = 0;
	}


	AssetManager::~AssetManager()
	{
	}

	void AssetManager::loadMeshes()
	{
		meshes[meshCount].loadMesh("Assets/Models/colorcube.dae");
		meshes[meshCount].genBufs();
	}
	void AssetManager::createModels()
	{
		meshTransMat[meshTransMatCount++] = Mat4x4<float>((Mat3x3<float>::getIdentMat()*0.15f), Vec3D<float>(0.f, 0.f, 0.f));
		meshTransMat[meshTransMatCount++] = Mat4x4<float>((Mat3x3<float>::getIdentMat()*0.2f), Vec3D<float>(1.f, 0.f, 0.f));
	}
	bool AssetManager::hasMoreModels()
	{
		if (meshIterCounter < meshTransMatCount)
		{
			meshIterCounter++;
			return true;
		}
		else
		{
			meshIterCounter = 0;
			return false;
		}
	}
	void AssetManager::getNextModel(Mesh &m, float f[16])
	{
		m = meshes[0];
		meshTransMat[meshIterCounter-1].toArray(f);
	}
}
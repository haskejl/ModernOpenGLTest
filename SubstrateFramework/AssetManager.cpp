#include "AssetManager.h"

namespace ssfw
{
	AssetManager::AssetManager()
	{
		modelCount = 0;
		meshCount = 0;
		modelIterCounter = 0;
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
		Mat4x4<float> transMat = Mat4x4<float>((Mat3x3<float>::getIdentMat()*0.2f), Vec3D<float>(0.f, 0.f, 0.f));
		models[modelCount++].create(meshes[0], transMat);
		transMat =  Mat4x4<float>((Mat3x3<float>::getIdentMat()*0.2f), Vec3D<float>(1.f, 0.f, 0.f));
		models[modelCount++].create(meshes[0], transMat);
	}
	bool AssetManager::hasMoreModels()
	{
		if (modelIterCounter < modelCount)
		{
			return true;
		}
		else
		{
			modelIterCounter = 0;
			return false;
		}
	}
	void AssetManager::getNextModel(Mesh &m, float f[16])
	{
		m = models[modelIterCounter].getMesh();
		models[modelIterCounter++].getTransMat().toArray(f);
	}
}
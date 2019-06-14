#include "AssetManager.h"

namespace ssfw
{
	//Constructor creates a new AssetManager
	AssetManager::AssetManager()
	{
		modelCount = 0;
		modelIterCounter = 0;
	}//end AssetManager() constructor

	//Default destructor
	AssetManager::~AssetManager()
	{
	}//end ~AssetManager() destructor

	//Loads in the meshes
	//TODO: add ability to control from a file
	void AssetManager::loadMeshes()
	{
		Mesh m;
		m.loadMesh("Assets/Models/colorcube.dae");
		m.genBufs();
		meshMap.emplace("colorcube", m);
	}//end loadMeshes() method

	//Creates the models using meshes
	//TODO: add ability to load in model files
	void AssetManager::createModels()
	{
		Mat4x4<float> transMat = Mat4x4<float>((Mat3x3<float>::getIdentMat()*0.2f), Vec3D<float>(0.f, 0.f, 0.f));
		std::string s = "colorcube";
		models[modelCount++].create(s, transMat);
		transMat =  Mat4x4<float>((Mat3x3<float>::getIdentMat()*0.2f), Vec3D<float>(1.f, 0.f, 0.f));
		models[modelCount++].create(s, transMat);
	}//end createModels() method

	//Method to iterate through the array of models. Once at the end of the list resets to the first element in the array
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
	}//end hasMoreModels() method

	//Returns the next model in the list in the form of a Mesh and array of floats
	void AssetManager::getNextModel(Mesh &m, float f[16])
	{
		m = meshMap[models[modelIterCounter].meshID];
		models[modelIterCounter++].toWorldMat.toArray(f);
	}//end getNextModel(&Mesh, float[16])
}
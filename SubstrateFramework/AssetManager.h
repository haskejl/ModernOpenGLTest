#pragma once

#include "FileLoader.h"
#include "Logger.h"
#include "Mesh.h"

namespace ssfw
{
	class AssetManager
	{
	private:
		Mat4x4<float> meshTransMat[1000];
		Mesh meshes[100];

		int meshTransMatCount;
		int meshCount;
		int meshIterCounter;

	public:
		AssetManager();
		~AssetManager();

		void loadMeshes();
		void createModels();

		bool hasMoreModels();
		void getNextModel(Mesh &m, float f[16]);
	};
}
#pragma once

#include "FileLoader.h"
#include "Logger.h"
#include "Mesh.h"
#include "Model.h"

namespace ssfw
{
	class AssetManager
	{
	private:
		Mesh meshes[100];
		Model models[1000];

		int modelCount;
		int meshCount;
		int modelIterCounter;

	public:
		AssetManager();
		~AssetManager();

		void loadMeshes();
		void createModels();

		bool hasMoreModels();
		void getNextModel(Mesh &m, float f[16]);
	};
}
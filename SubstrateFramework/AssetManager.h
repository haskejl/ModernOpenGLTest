#pragma once

#include <map>
#include <string>

#include "FileLoader.h"
#include "Logger.h"
#include "Mesh.h"
#include "Model.h"

namespace ssfw
{
	class AssetManager
	{
	private:
		std::map<std::string, Mesh> meshMap;
		//TODO: make vector<Model> models
		Model models[1000];

		int modelCount;
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
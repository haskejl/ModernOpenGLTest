#pragma once

#include <string>
#include <regex>
#include <vector>
#include <assert.h>

#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "FileLoader.h"
#include "Math.h"
#include "Logger.h"
#include "Material.h"
namespace ssfw
{
	class Mesh
	{
	public:
		std::vector<Material> materials;

		VertexBuffer *vertBuf;

	private:
		std::vector<float> vertices;
		Mat4x4<float> modelMat;

		void processMatProp4f(std::string &line, float f[4]);
		void removeOpeningTag(std::string &line);
		void removeExponents(std::string &line);

	public:
		Mesh();
		~Mesh();

		void loadMesh(std::string filePath);
		void genBufs();
	};
}

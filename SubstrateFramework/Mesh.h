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

namespace ssfw
{
	class Mesh
	{
	public:
		struct Material
		{
			IndexBuffer *indBuf;

			std::string matID;
			std::vector<unsigned int> indices;

			float *emission;
			float *ambient;
			float *diffuse;
			float *specular;
			float shininess;

			Material(std::string mID)
			{
				emission = new float[4];
				ambient = new float[4];
				diffuse = new float[4];
				specular = new float[4];

				matID = mID;
			}
			Material(std::string mID, int ind[], float emi[], float amb[], float dif[], float spec[], float shi)
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
			~Material()
			{
				indices.~vector();
			}

			void genBufs()
			{
				indBuf = new IndexBuffer(indices, GL_STATIC_DRAW);
			}
		};

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

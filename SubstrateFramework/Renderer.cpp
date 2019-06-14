#include "Renderer.h"

namespace ssfw
{
	Renderer::Renderer()
	{
		cam = new Camera(-1.5f, 1.5f, -2.f, 2.f, -1.f, 1.f);
		am.loadMeshes();
		am.createModels();
		//Shader Setup
		shader = compileShaders(loadShaderFile("VertShader.shader"), loadShaderFile("FragShader.shader"));
		//Vertex Array Setup
		glGenVertexArrays(1, &vertArray);
		glBindVertexArray(vertArray);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	}

	Renderer::~Renderer()
	{
		delete cam;
	}

	void Renderer::draw()
	{
		float modMatA[16];
		float viewMatA[16];
		float projMatA[16];
		cam->getViewMat().toArray(viewMatA);
		cam->getProjMat().toArray(projMatA);

		//Draw objects
		glUseProgram(shader);
		int location = glGetUniformLocation(shader, "vertColor");
		int locModMat = glGetUniformLocation(shader, "modMat");
		int locViewMat = glGetUniformLocation(shader, "viewMat");
		int locProjMat = glGetUniformLocation(shader, "projMat");
		glBindBuffer(GL_ARRAY_BUFFER, vertArray);

		while (am.hasMoreModels())
		{
			Mesh m;
			am.getNextModel(m, modMatA);
			m.vertBuf->bind();
			for (int i = 0; i < m.materials.size(); i++)
			{
					m.materials[i].indBuf->bind();
				glUniform4f(location, m.materials[i].specular[0], m.materials[i].specular[1], m.materials[i].specular[2], m.materials[i].specular[3]);
				glUniformMatrix4fv(locModMat, 1, false, &modMatA[0]);
				glUniformMatrix4fv(locViewMat, 1, false, &viewMatA[0]);
				glUniformMatrix4fv(locProjMat, 1, false, &projMatA[0]);

				glBindVertexArray(vertArray);
				glDrawElements(GL_TRIANGLES, m.materials[i].indices.size(), GL_UNSIGNED_INT, nullptr);
			}
		}
	}

	void Renderer::moveCamera(Vec3D<float> movVec)
	{
		Mat4x4<float> transMat(Mat3x3<float>::getIdentMat(), movVec);
		cam->updateViewMat(transMat);
	}
	void Renderer::moveCamera(Mat3x3<float> rotMat)
	{
		Mat4x4<float> transMat(rotMat, Vec3D<float>(0.f, 0.f, 0.f));
		cam->updateViewMat(transMat);
	}
	void Renderer::moveCamera(Vec3D<float> movVec, Mat3x3<float> rotMat)
	{
		Mat4x4<float> transMat(rotMat, movVec);
		cam->updateViewMat(transMat);
	}
	//Gives the illusion of zooming in by scaling the view matrix
	void Renderer::moveCamera(float scalar)
	{
		Mat4x4<float>transMat(Mat3x3<float>::getIdentMat()*scalar, Vec3D<float>(0.f, 0.f, 0.f));
		cam->updateViewMat(transMat);
	}
}
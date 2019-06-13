#include "Renderer.h"

namespace ssfw
{
	Renderer::Renderer()
	{
		cam = new Camera(-1.5f, 1.5f, -2.f, 2.f, -1.f, 1.f);
		cube.loadMesh("Assets/Models/colorcube.dae");
		cube.genBufs();
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
		Mat3x3<float> scale = Mat3x3<float>::getIdentMat()*0.5f;
		Mat3x3<float> rot = Mat3x3<float>::getRotX(40);
		rot = Mat3x3<float>::getRotY(10) * rot;
		Mat4x4<float>::Mat4x4<float>(scale * rot , Vec3D<float>(0.f, 0.f, 0.f)).toArray(modMatA);
		cam->getViewMat().toArray(viewMatA);
		cam->getProjMat().toArray(projMatA);
		
		//fMat.print();

		//Draw objects
		glUseProgram(shader);
		int location = glGetUniformLocation(shader, "vertColor");
		int locModMat = glGetUniformLocation(shader, "modMat");
		int locViewMat = glGetUniformLocation(shader, "viewMat");
		int locProjMat = glGetUniformLocation(shader, "projMat");
		glBindBuffer(GL_ARRAY_BUFFER, vertArray);
		cube.vertBuf->bind();
		for (int i = 0; i < cube.materials.size(); i++)
		{
			cube.materials[i].indBuf->bind();
			glUniform4f(location, cube.materials[i].specular[0], cube.materials[i].specular[1], cube.materials[i].specular[2], cube.materials[i].specular[3]);
			glUniformMatrix4fv(locModMat, 1, false, &modMatA[0]);
			glUniformMatrix4fv(locViewMat, 1, false, &viewMatA[0]);
			glUniformMatrix4fv(locProjMat, 1, false, &projMatA[0]);

			glBindVertexArray(vertArray);
			glDrawElements(GL_TRIANGLES, cube.materials[i].indices.size(), GL_UNSIGNED_INT, nullptr);
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
}
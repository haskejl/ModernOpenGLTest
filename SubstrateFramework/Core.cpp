#include "Core.h"

namespace ssfw
{
	Core::Core()
	{
	}

	Core::~Core()
	{
	}

	void Core::start()
	{
		if (!glfwInit())
		{
			Logger::printErrMsg("GLFW failed to initialize!", 10);
		}

		//Setup OpenGL Version and Options
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glClearColor(0.f, 0.f, 0.f, 1.f);

		//Create a window using GLFW
		window = glfwCreateWindow(640, 480, "SubstrateFrameworkGame", NULL, NULL);

		if (!window)
		{
			glfwTerminate();
			Logger::printErrMsg("Failed to create window!", 10);
		}

		//Setup GLFW options
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		if (glewInit() != GLEW_OK)
		{
			Logger::printErrMsg("GLEW failed to initialize!", 10);
		}

		//float positions[] =
		//{
		//	-0.5f, -0.5f, 0.f,
		//	0.5f, -0.5f, 0.f,
		//	0.5f, 0.5f, 0.f,
		//	-0.5f, 0.5f, 0.f
		//};
		//unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

		float positions_s[] =
		{
			0.5f, 0.5f, -0.5f,
			0.5f, -0.5f, -0.5f,
			-0.5f, -0.5f, -0.5f,
			-0.5f, 0.5f, -0.5f,
			0.5f, 0.5f, 0.5f,
			0.5f, -0.5f, 0.5f,
			-0.5f, -0.5f, 0.5f,
			-0.5f, 0.5f, 0.5f
		};

		float positions[24];
		for (int i = 0; i < 24; i++)
			positions[i] = positions_s[i];

		unsigned int indices[] = { 7, 5, 4, 7, 6, 5 };
		unsigned int indices0[] = { 4, 1, 0, 4, 5, 1 };
		unsigned int indices1[] = { 5, 2, 1, 5, 6, 2 };
		unsigned int indices2[] = { 0, 2, 3, 0, 1, 2 };
		unsigned int indices3[] = { 0, 7, 4, 0, 3, 7 };
		unsigned int indices4[] = { 2, 7, 3, 2, 6, 7 };

		unsigned int vertArray, vertBuffer, indBuffer;

		//Vertex Array Setup
		glGenVertexArrays(1, &vertArray);
		glBindVertexArray(vertArray);

		//Vertex Buffer Setup
		glGenBuffers(1, &vertBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);

		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		//Index Buffer Setup
		glGenBuffers(1, &indBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBuffer);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		//Shader Setup
		uint32_t shader = compileShaders(loadShaderFile("VertShader.shader"), loadShaderFile("FragShader.shader"));

		//Clear the buffers
		glBindVertexArray(0);
		glUseProgram(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		float rot = 0;
		
		while (!glfwWindowShouldClose(window))
		{
			for (int i = 0; i < 24; i+=3)
			{
				Vec3D<float> v(positions_s[i], positions_s[i + 1], positions_s[i + 2]);
				Mat3x3<float> xRot = Mat3x3<float>::getRotX(rot);
				Mat3x3<float> yRot = Mat3x3<float>::getRotY(rot / 2);
				Mat3x3<float> zRot = Mat3x3<float>::getRotZ(45);
				Mat4x4<float> mRot((zRot*yRot*xRot), Vec4D<float>(0.f, 0.f, 0.f, 1.f));
				v = mRot * v;
				positions[i]	= v.getX();
				positions[i + 1]= v.getY();
				positions[i + 2]= v.getZ();
			}
			rot += 0.25f;
			glBindBuffer(GL_ARRAY_BUFFER, vertArray);
			glBufferSubData(GL_ARRAY_BUFFER, 0.f, sizeof(positions), positions);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0.f, sizeof(indices), indices);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(shader);
			
			int location = glGetUniformLocation(shader, "vertColor");
			glUniform4f(location, 0.64f, 0.64f, 0.64f, 1.f);
			glBindVertexArray(vertArray);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			/////////////////////////////////////////////////////////////////
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0.5, sizeof(indices0), indices0);
			glUniform4f(location, 0.64f, 0.03419028f, 0.04508092f, 1.f);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			/////////////////////////////////////////////////////////////////
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0.5, sizeof(indices1), indices1);
			glUniform4f(location, 0.6322616f, 0.008009382f, 0.64f, 1.f);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			/////////////////////////////////////////////////////////////////
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0.5, sizeof(indices2), indices2);
			glUniform4f(location, 0.01013024, 0.007439202f, 0.64f, 1.f);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			/////////////////////////////////////////////////////////////////
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0.5, sizeof(indices3), indices3);
			glUniform4f(location, 0.f, 0.64f, 0.f, 1.f);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			/////////////////////////////////////////////////////////////////
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0.5, sizeof(indices4), indices4);
			glUniform4f(location, 0.4074062f, 0.64f, 0.008990522f, 1.f);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
	}
}

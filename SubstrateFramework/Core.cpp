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

		window = glfwCreateWindow(640, 480, "SubstrateFrameworkGame", NULL, NULL);

		if (!window)
		{
			glfwTerminate();
			Logger::printErrMsg("Failed to create window!", 10);
		}

		glfwMakeContextCurrent(window);

		if (glewInit() != GLEW_OK)
		{
			Logger::printErrMsg("GLEW failed to initialize!", 10);
		}

		Triangle t(Vec3D<float>(-0.5f, -0.5f, 1.f), Vec3D<float>(0.f, 0.5f, 1.f), Vec3D<float>(0.5f, 0.5f, 1.f));

		float positions[3 * 3] =
		{
			-0.5f, -0.5f, 0.f,
			0.5f, -0.5f, 0.f,
			0.0f, 0.5f, 0.f
		};

		uint32_t shader = compileShaders(loadShaderFile("VertShader.shader"), loadShaderFile("FragShader.shader"));

		unsigned int vertArray, vertBuffer, indBuffer;

		//Vertex Array
		glGenVertexArrays(1, &vertArray);
		glBindVertexArray(vertArray);
		//Vertex Buffer
		glGenBuffers(1, &vertBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);

		glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		//Index Buffer
		glGenBuffers(1, &indBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		//Shader

		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.2f, 0.2f, 0.2f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(shader);

			glBindVertexArray(vertArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);


			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
	}
}

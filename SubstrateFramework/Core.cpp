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

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

		if (glewInit() != GLEW_OK)
		{
			Logger::printErrMsg("GLEW failed to initialize!", 10);
		}

		float positions[] =
		{
			-0.5f, -0.5f, 0.f,
			0.5f, -0.5f, 0.f,
			0.5f, 0.5f, 0.f,
			-0.5f, 0.5f, 0.f
		};
		unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

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

		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(shader);
			
			int location = glGetUniformLocation(shader, "vertColor");
			glUniform4f(location, 0.f, 1.f, 0.9f, 1.f);
			glBindVertexArray(vertArray);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
	}
}

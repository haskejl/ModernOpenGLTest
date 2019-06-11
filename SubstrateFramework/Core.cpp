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

		/*float positions_s[] =
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

		unsigned int indices[6][6] = 
		{
			{ 7, 5, 4, 7, 6, 5 },
			{ 4, 1, 0, 4, 5, 1 },
			{ 5, 2, 1, 5, 6, 2 },
			{ 0, 2, 3, 0, 1, 2 },
			{ 0, 7, 4, 0, 3, 7 },
			{ 2, 7, 3, 2, 6, 7 }
		};*/
		Mesh cube;
		cube.loadMesh("Assets/Models/colorcube.dae");
		cube.genBufs();

		unsigned int vertArray;

		//Vertex Array Setup
		glGenVertexArrays(1, &vertArray);
		glBindVertexArray(vertArray);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		//Shader Setup
		uint32_t shader = compileShaders(loadShaderFile("VertShader.shader"), loadShaderFile("FragShader.shader"));

		float rot = 0;
		
		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(shader);
			
			int location = glGetUniformLocation(shader, "vertColor");
			cube.vertBuf->bind();
			for (int i = 0; i < cube.materials.size(); i++)
			{
				//glUniform4f(location, cube.materials[i].diffuse[0], cube.materials[i].diffuse[1], cube.materials[i].diffuse[2], cube.materials[i].diffuse[3]);
				glUniform4f(location, 0.3f, 0.3f, 0.3f, 1.f);
				cube.materials[i].indBuf->bind();
				glBindVertexArray(vertArray);
				glDrawElements(GL_TRIANGLES, cube.materials[i].indices.size(), GL_UNSIGNED_INT, nullptr);
			}
			
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
	}
}

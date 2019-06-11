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
			0.5f, -0.5f, -0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f, -0.5f, 0.5f, 0.5f, 0.5f
		};

		float positions[24];
		for (int i = 0; i < 24; i++)
			positions[i] = positions_s[i];

		unsigned int indices[] = { 3, 0, 1, 7, 2, 3, 5, 6, 7, 1, 4, 5, 2, 4, 0, 7, 1, 5, 3, 2, 0, 7, 6, 2, 5, 4, 6, 1, 0, 4, 2, 6, 4, 7, 3, 1 };

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
		float rot = 0.f;
		
		while (!glfwWindowShouldClose(window))
		{
			for (int i = 0; i < 24; i+=3)
			{
				Vec3D<float> v(positions_s[i], positions_s[i + 1], positions_s[i + 2]);
				Mat4x4<float> mRot(Mat3x3<float>::getRotZ(rot), Vec4D<float>(0.f, 0.f, 0.f, 1.f));
				v = mRot * v;
				positions[i]	= v.getX();
				positions[i + 1]= v.getY();
				positions[i + 2]= v.getZ();
			}
			rot += 0.5f;
			glBindBuffer(GL_ARRAY_BUFFER, vertArray);
			glBufferSubData(GL_ARRAY_BUFFER, 0.f, sizeof(positions), positions);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(shader);
			
			int location = glGetUniformLocation(shader, "vertColor");
			glUniform4f(location, 0.f, 1.f, 0.9f, 1.f);
			glBindVertexArray(vertArray);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);


			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
	}
}

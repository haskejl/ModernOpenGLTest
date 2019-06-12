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

		setOpenGLVersion();

		//Create a window using GLFW
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

		setWindowSettings();

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
			Mat3x3<float> rotX = Mat3x3<float>::getRotX(45);
			Mat3x3<float> rotY = Mat3x3<float>::getRotY(rot);
			Mat3x3<float> rotZ = Mat3x3<float>::getRotZ(rot / 2);

			rot += 0.25f;
			if (rot > 720.f) rot = 0.f;
			Mat4x4<float> transMat(rotX*rotY*rotZ, Vec3D<float>(0.f, 0.f, 0.f));
			cube.srt(0.15f, transMat);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glUseProgram(shader);
			
			int location = glGetUniformLocation(shader, "vertColor");
			glBindBuffer(GL_ARRAY_BUFFER, vertArray);
			cube.vertBuf->bind();
			for (int i = 0; i < cube.materials.size(); i++)
			{
				cube.materials[i].indBuf->bind();
				glUniform4f(location, cube.materials[i].specular[0], cube.materials[i].specular[1], cube.materials[i].specular[2], cube.materials[i].specular[3]);
				glBindVertexArray(vertArray);
				glDrawElements(GL_TRIANGLES, cube.materials[i].indices.size(), GL_UNSIGNED_INT, nullptr);
			}
			
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
		glfwTerminate();
	}

	//Setup the OpenGL version and profile
	void Core::setOpenGLVersion()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	//Setup the GLFW window settings
	void Core::setWindowSettings()
	{
		glfwSwapInterval(1);
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glfwSetKeyCallback(window, key_callback);
	}
}

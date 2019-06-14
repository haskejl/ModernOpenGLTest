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
		Renderer renderer;
		glfwSetWindowUserPointer(window, (void *)&renderer);

		while (!glfwWindowShouldClose(window))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			renderer.draw();
			
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
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	}

	//Setup the GLFW window settings
	void Core::setWindowSettings()
	{
		glfwSwapInterval(1);
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClearDepth(10.f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glfwSetKeyCallback(window, key_callback);
		glViewport(0, 0, 640, 480);
		//glDepthRangef(0.2f, 10.f);
	}

	void Core::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		Renderer *rend = (Renderer *)glfwGetWindowUserPointer(window);
		if (key == GLFW_KEY_W && action == GLFW_PRESS)
			rend->moveCamera(Vec3D<float>(0.f, 0.1f, 0.f));
		else if (key == GLFW_KEY_S && action == GLFW_PRESS)
			rend->moveCamera(Vec3D<float>(0.f, -0.1f, 0.f));
		else if (key == GLFW_KEY_A && action == GLFW_PRESS)
			rend->moveCamera(Vec3D<float>(-0.1f, 0.f, 0.f));
		else if (key == GLFW_KEY_D && action == GLFW_PRESS)
			rend->moveCamera(Vec3D<float>(0.1f, 0.f, 0.f));
		else if (key == GLFW_KEY_E && action == GLFW_PRESS)
			rend->moveCamera(Mat3x3<float>::getRotY(5));
		else if (key == GLFW_KEY_F && action == GLFW_PRESS)
			rend->moveCamera(0.95f);
		else if (key == GLFW_KEY_R && action == GLFW_PRESS)
			rend->moveCamera(1.05f);
	}
}

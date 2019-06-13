#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Math.h"
#include "Logger.h"
#include "Renderer.h"

namespace ssfw
{
	class Core
	{
	private:
		GLFWwindow *window;

		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	public:
		Core();
		virtual ~Core();

		void start();
		void setOpenGLVersion();
		void setWindowSettings();
	};
}


#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "FileLoader.h"
#include "Math.h"
#include "Geometry.h"
#include "Logger.h"
#include "Shader.h"
#include "Mesh.h"
#include "Keyboard.h"

namespace ssfw
{
	class Core
	{
	private:
		GLFWwindow *window;
	public:
		Core();
		virtual ~Core();

		void start();
		void setOpenGLVersion();
		void setWindowSettings();
	};
}


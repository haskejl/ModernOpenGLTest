#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "FileLoader.h"
#include "Geometry.h"
#include "Logger.h"
#include "Math.h"
#include "Shader.h"

class Core
{
private:
	GLFWwindow *window;
public:
	Core();
	virtual ~Core();

	void start();
};


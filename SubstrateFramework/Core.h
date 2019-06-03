#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Geometry.h"
#include "Logger.h"
#include "Math.h"

class Core
{
private:
	GLFWwindow *window;
public:
	Core();
	virtual ~Core();

	void start();
};


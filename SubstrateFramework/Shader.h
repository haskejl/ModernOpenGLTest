#pragma once

#include <string>
#include <GL/glew.h>
#include <vector>

#include "Logger.h"

static std::string vertShad = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertColor;

void main()
{
	gl_Position = vec4(aPos, 1.0);
	vertColor = vec4(0.5, 0.0, 0.0, 1.0);
}
)";

static std::string fragShad = R"(
#version 330 core
out vec4 fragColor;

in vec4 vertColor;

void main()
{
	fragColor = vertColor;
}
)";

static uint32_t compileShaders(std::string vs, std::string fs)
{
	//Read shaders into the appropriate buffers
	std::string vSrc = vs;
	std::string fSrc = fs;

	//Create an empty vertex shader
	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Send the vertex shader code to GL. std::string.c_str is NULL terminated
	const char *src = (const char *)vSrc.c_str();
	glShaderSource(vertexShader, 1, &src, 0);

	//Compile the vertex shader
	glCompileShader(vertexShader);

	int32_t isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		int32_t maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		//maxLength includes the NULL character
		std::vector<char> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		//Delete the shader
		glDeleteShader(vertexShader);

		std::string temp(infoLog.begin(), infoLog.end());
		Logger::printErrMsg(temp, 10);

		return -1;
	}

	//Create an empty fragment shader
	uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Send the fragment shader source code to GL
	src = (const char *)fSrc.c_str();
	glShaderSource(fragmentShader, 1, &src, 0);

	//Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		int32_t maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		glDeleteShader(fragmentShader);
		glDeleteShader(vertexShader);

		std::string temp(infoLog.begin(), infoLog.end());
		Logger::printErrMsg(temp, 10);

		return -1;
	}

	//Compiled Successfully
	uint32_t program = glCreateProgram();
	
	//Attach shaders to the program
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	//Link the program
	glLinkProgram(program);

	int32_t isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
	if (isLinked == GL_FALSE)
	{
		int32_t maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		//Cleanup
		glDeleteProgram(program);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		std::string temp(infoLog.begin(), infoLog.end());
		Logger::printErrMsg(temp, 10);

		return -1;
	}

	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}
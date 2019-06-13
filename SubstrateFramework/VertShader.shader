#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 modMat;
uniform mat4 viewMat;
uniform mat4 projMat;

void main()
{
	vec4 pos = vec4(aPos, 1.0);
	gl_Position = (projMat * viewMat * modMat * pos);
}
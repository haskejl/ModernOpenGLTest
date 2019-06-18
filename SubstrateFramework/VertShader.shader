#version 330 core
layout (location = 0) in vec3 aPos;
layout(location = 1) in vec3 norms;

uniform mat4 modMat;
uniform mat4 viewMat;
uniform mat4 projMat;

uniform vec4 emisIn;
uniform vec4 ambIn;
uniform vec4 diffIn;
uniform vec4 specIn;
uniform float shinIn;

out vec4 colorOut;

void main()
{
	vec4 lgtVec = viewMat*vec4(0.7, 0.7, 0.0, 1.0);
	vec4 pos = vec4(aPos, 1.0);

	colorOut = specIn;
	gl_Position = (projMat * viewMat * modMat * pos);
}
#version 440 core

layout (location = 0) in vec3 a_Pos;

out vec3 v_Pos;

void main()
{
	v_Pos = a_Pos;
	gl_Position = vec4(a_Pos, 1.0);
}
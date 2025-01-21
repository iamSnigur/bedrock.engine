#version 440 core

layout (location = 0) in vec3 a_Pos;

out vec3 v_Pos;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;

void main()
{
	v_Pos = a_Pos;	
	gl_Position = u_ViewProjection * u_Model * vec4(a_Pos, 1.0);
}
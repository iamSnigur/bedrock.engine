#shader vertex
#version 440 core

layout (location = 0) in vec3 a_Pos;

out vec3 v_Pos;

uniform mat4 u_ViewProjection;

void main()
{
	v_Pos = a_Pos;
	gl_Position = u_ViewProjection * vec4(a_Pos, 1.0);
}

#shader fragment
#version 440 core

layout (location = 0) out vec4 color;

in vec3 v_Pos;

void main()
{
	color = vec4(v_Pos * 0.15 + 0.5, 1.0);
}
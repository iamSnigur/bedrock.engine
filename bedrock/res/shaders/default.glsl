#shader vertex
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

#shader fragment
#version 440 core

layout (location = 0) out vec4 fragColor;

in vec3 v_Pos;

void main()
{
	vec3 normal = normalize(cross(dFdx(v_Pos), dFdy(v_Pos)));
	float diffuse = max(dot(normal, normalize(vec3(0.1, 0.1, 0.1))), 0.35);
	vec3 baseColor = v_Pos * 0.5 + 0.5;
    vec3 shadedColor = baseColor * diffuse;
	fragColor = vec4(shadedColor, 1.0);
}
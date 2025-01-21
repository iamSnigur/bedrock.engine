#version 440 core

#define pi 3.14159265359

layout (location = 0) out vec4 fragColor;

in vec3 v_Pos;

float saw(float x)
{
    return abs(fract(x) - 0.5) * 2.0;
}

float dw(vec2 p, vec2 c, float t)
{
    return sin(length(p - c) - t);
}

float dw1(vec2 uv)
{
    float v = 0.0;
    float t = v_Pos.z * 2.0; // time
    v += dw(uv, vec2(sin(t * 0.07) * 30.0, cos(t * 0.04) * 20.0), t * 1.3);
    v += dw(uv, vec2(cos(t * 0.13) * 30.0, sin(t * 0.14) * 20.0), t * 1.6 + 1.0);
    v += dw(uv, vec2( 18,-15),t * 0.7 + 2.0);
    v += dw(uv, vec2(-18, 15),t * 1.1 - 1.0);

    return v/4.0;
}

float fun(float x, float y)
{
	return dw1(vec2(x - 0.5, y - 0.5) * 80.0);
}

vec3 duv(vec2 uv)
{
    float x = uv.x;
    float y = uv.y;
    float v = fun(x,y);
    float d = 1.0 / 400.0;
	float dx = (v - fun(x + d, y)) / d;
	float dy = (v - fun(x, y + d)) / d;
    float a = atan(dx, dy) / pi / 2.0;

    return vec3(v, 0, (v * 4.0 + a));
}

void main()
{
	vec3 normal = normalize(cross(dFdx(v_Pos), dFdy(v_Pos)));
	float diffuse = max(dot(normal, normalize(vec3(0.1, 0.1, 0.1))), 0.35);

    vec2 uv = gl_FragCoord.xy / 1920.0;
    vec3 h = duv(uv); 
    float sp = saw(h.z + v_Pos.z * 1.3); // time    
    sp = clamp((sp - 0.25) * 2.0, 0.5, 1.0);

    vec3 baseColor = vec3(
            (h.x + 0.5) * sp, 
            (0.3 + saw(h.x + 0.5) * 0.6) * sp,
            (0.6 - h.x) * sp);

    vec3 shadedColor = baseColor * diffuse;
    fragColor = vec4(shadedColor, 1.0);
}
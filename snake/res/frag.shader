#version 410 core

layout(location = 0) out vec4 o_color;

in vec3 v_color;

void main()
{
	o_color = vec4(v_color, 1.0f);
}
#version 330 core
layout(location = 0) in vec2 coord2d;

out vec2 f_texcoord;

void main(void)
{
	gl_Position = vec4(coord2d, 0.0, 1.0);
	// temp to fix mirror
	vec2 temp = coord2d; //(coord2d + 1.0) / 2.0;
	temp.x = temp.x;
	temp.y = -temp.y;
	f_texcoord = temp;
}
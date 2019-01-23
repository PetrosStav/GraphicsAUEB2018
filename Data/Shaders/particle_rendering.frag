#version 330 core
layout(location = 0) out vec4 out_color;

uniform vec3 uniform_color;

void main(void) 
{
	out_color = vec4( uniform_color, 1.0);	
}


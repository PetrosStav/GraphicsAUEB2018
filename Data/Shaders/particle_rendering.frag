#version 330 core
layout(location = 0) out vec4 out_color;

uniform vec3 uniform_color;
uniform float uniform_type;

in float rand1;
//in float rand2;

void main(void) 
{
	vec3 color = uniform_color;
	if(uniform_type>=2-0.1 && uniform_type<=2+0.1){
		// Confetti
		//color.r += 0.8 * rand1;
		//color.g -= rand2;
		//color.b += 0.8 * (rand1 * rand2);
		
		// Green variant
		color.g -= 0.6*rand1;
		
	}
	out_color = vec4( color, 0.4);	
}


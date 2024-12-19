#version 330 core		

//since i m using 3 cartesiaon plane
//layout means vertex array papges on page 0 i have stred positions and page 1 i have stored color value  for now 


layout(location = 0 ) in vec3 Tripoints;
layout(location = 1 ) in vec3 Color;
											
out  vec3 pixColor;
																						
void main(){								
	gl_Position = vec4( Tripoints , 1.0f );	
	pixColor = Color;
}										
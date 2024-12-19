#version 330 core							

layout(location = 0 ) out vec4 PixelCOLOR;		

in vec3 pixColor;

//uniform vec4 U_color;						

void main(){								
	PixelCOLOR = vec4(pixColor,1.0);			
}											
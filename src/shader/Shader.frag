#version 430 core

in vec3 vertexColor;  // Input from vertex shader
out vec4 FragColor;   // Output to the framebuffer

void main() {
    FragColor = vec4(vertexColor, 1.0);  // Output the color with full opacity (alpha = 1.0)
}

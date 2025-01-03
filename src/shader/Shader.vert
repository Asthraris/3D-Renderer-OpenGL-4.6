#version 330 core

layout(location = 0) in vec3 vPos;   // Position attribute
layout(location = 1) in vec3 vColor; // Color attribute
layout(location = 2) in vec3 vNormal;
layout(location = 3) in mat4 ModelMatrix;

out vec3 vertexColor;  // Output to fragment shader
out vec3 Normal;
out vec3 fragPos; 


uniform mat4 finalMatrix;

void main() {
    gl_Position = finalMatrix * ModelMatrix * vec4(vPos , 1.0f);    // Directly pass the position to gl_Position
    vertexColor = vColor;                                       // Pass the color to the fragment shader
    fragPos = (ModelMatrix * vec4(vPos , 1.0f)).xyz;
    Normal = mat3(transpose(inverse(ModelMatrix))) * vNormal;
}
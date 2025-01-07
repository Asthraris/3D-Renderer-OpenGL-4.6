#version 330 core

layout(location = 0) in vec3 vPos;   // Position attribute
layout(location = 1) in vec3 vColor; // Color attribute
layout(location = 2) in vec3 vNormal;
layout(location = 3) in vec2 vTexCords;
layout(location = 4) in mat4 ModelMatrix;

out vec3 vertexColor;  // Output to fragment shader
out vec2 Tex_cordinates;
out vec3 normal;
out vec3 currFragPos; 


uniform mat4 finalMatrix;

void main() {
        
    vertexColor = vColor;                                       // Pass the color to the fragment shader
    Tex_cordinates = vTexCords;
    
        // hum normal, currFragPos ko bhi interpolate karke bhejte hai isliye agar 2 vertices me diff normal hai toh khud bich ke normal genrate ho jate hai
    currFragPos = (ModelMatrix * vec4(vPos , 1.0f)).xyz;
    normal =mat3(transpose(inverse(ModelMatrix))) * vNormal;;
        // iske model mat bina ye cube ka transformation ko ignore karta hai so even when cube is rotated it will only have one side lighed not like real
        //gl_Position inbuilt var hai jo position of vertices denote karta hai while rendering
    gl_Position = finalMatrix * ModelMatrix * vec4(vPos , 1.0f);    // Directly pass the position to gl_Position
}
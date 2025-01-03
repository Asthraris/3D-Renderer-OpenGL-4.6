#version 330 core

in vec3 vertexColor;  // Input from vertex shader
in vec3 Normal;
in vec3 fragPos;

out vec4 FragColor;   // Output to the framebuffer

uniform vec3 sunPos;
uniform float rayIntensity;
uniform vec3 lightColor;

uniform float AmbientIntensity;

void main() {
    // Calculate direction from the light source to the fragment
    vec3 lightDir = normalize(sunPos - fragPos);

    // Calculate diffuse lighting (Lambertian)
    float diff = max(dot(lightDir, Normal), 0.0);

    // Calculate ambient light based on intensity
    vec3 ambientLight = AmbientIntensity * lightColor;

    // Calculate diffuse light based on the angle between light and surface normal
    vec3 diffuseLight = diff * lightColor * rayIntensity;

    // Final color combining ambient and diffuse light with the vertex color
    vec3 finalColor = (ambientLight + diffuseLight) * vertexColor;

    // Output the final color with full opacity (alpha = 1.0)
    FragColor = vec4(finalColor, 1.0);
}

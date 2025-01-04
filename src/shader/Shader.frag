#version 330 core

in vec3 vertexColor;  // Input from vertex shader
in vec3 normal;
in vec3 currFragPos;

out vec4 FragColor;   // Output to the framebuffer

uniform vec3 CameraPosition;
uniform vec3 lightPosition;
    
uniform float rayIntensity;
uniform vec3 lightColor;

uniform float AmbientIntensity;






//least porfomance dec light
float calcAmbient(){
        // ambient agar shadow complete dark nhi chaiye tab use hota hai like in space where there in only one major lihjt source
    float ambientLight = AmbientIntensity ;

    return ambientLight;
}

//mid performance dec light
float calcDiffuse(vec3 Normal , vec3 lightDirection){

        // world cordinate me humne light dir find kiya in respect to object and light direction
        // yaha par currfragpos bhi interpolate hoke aaya hai ie. har pixel par hum calc kar sakte hai
        // REMEMBER: INPOLATION is very Important here
    

        // idhar dott product of two unit vec gives cos(x) between that 2 vec , yaha par -ve bhi aa sakta tha cos isliye humne 0.0 least set rakha hai nhi toh color ka opposite color show hoga were light dir and normal is not positive 
    float diff = max(dot(lightDirection, Normal), 0.0);

        // cos isliye kyuki agar x=0 than max intensity or x=90 then light is least , rayIntensity is strength of light
    float diffuseLight = diff  * rayIntensity;


    return diffuseLight;
}


//high performance dec light
float calcSpecular(vec3 Normal , vec3 lightDirection) {

    float specularStrength = 1.0f;  // Material shininess strength
    int specularExponent = 8; // Higher values = sharper highlights

    // Normalize camera position direction (view vector)
    vec3 ViewDir = normalize(CameraPosition - currFragPos);

    // Reflect light direction around the normal
    vec3 reflectedLightDir = reflect(-lightDirection, Normal);

    // Compute the specular angle
    float specAngle = max(dot(ViewDir, reflectedLightDir), 0.0f);

    // Apply shininess using exponentiation
    float specularLight = pow(specAngle, specularExponent) * specularStrength;

    return specularLight;
}



void main() {
        //humne normalize kiya normal ko to ensure its unit vector
    vec3 Normal = normalize(normal);
    vec3 lightDirection = normalize(lightPosition - currFragPos);
        
        // Final color combining ambient and diffuse light with the vertex color
    vec3 finalColor = (calcAmbient()+ calcDiffuse(Normal, lightDirection) + calcSpecular(Normal , lightDirection) ) * lightColor * vertexColor;

        // Output the final color with full opacity (alpha = 1.0)
    FragColor = vec4(finalColor, 1.0);
}

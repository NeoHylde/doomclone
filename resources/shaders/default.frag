#version 330 core

//Outputs colors in RGBA
out vec4 FragColor;

// Imports the current position from the Vertex Shader
in vec3 crntPos;
// Imports the normal from the Vertex Shader
in vec3 Normal;
//Inputs the color from the Vertex Shader
in vec3 color;
//Inputs the texture coordinates from the Vertex Shader
in vec2 texCoord;

//Gets the Texture Unit from the main function
uniform sampler2D diffuse0;

uniform sampler2D specular0;

uniform vec4 lightColor;
uniform vec3 camPos;
uniform vec3 lightPos;

vec4 pointLight() {
    vec3 lightVec = lightPos - crntPos;
    float dist = length(lightVec);
    float a = 3.0;
    float b = 0.7;
    float inten = 1.0f / (a * dist * dist + b * dist + 1.0f);

    float ambient = 0.20f;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightVec);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.50f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);

    float specular = specAmount * specularLight;

    return (texture(diffuse0, texCoord) * lightColor * (diffuse * inten + ambient) + texture(specular0, texCoord).r * specular * inten) * lightColor;
}

vec4 direcLight() {
    float ambient = 0.20f;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.50f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);

    float specular = specAmount * specularLight;

    return (texture(diffuse0, texCoord) * lightColor * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 spotLight() {
    float outerCone = 0.90f;
    float innerCone = 0.95f;
    float ambient = 0.20f;

    vec3 normal = normalize(Normal);
    vec3 lightDirection = normalize(lightPos - crntPos);
    float diffuse = max(dot(normal, lightDirection), 0.0f);

    float specularLight = 0.50f;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specAmount * specularLight;

    // Replace with uniform if needed
    vec3 spotDirection = normalize(vec3(0.0f, -1.0f, 0.0f));  
    float angle = dot(spotDirection, -lightDirection);
    float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

    return texture(diffuse0, texCoord) * lightColor * (diffuse * inten + ambient) + vec4(1.0) * specular * inten * texture(specular0, texCoord).r;
}


void main()
{
    FragColor = spotLight();
}
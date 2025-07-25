#version 330 core

// Position/Coordinates
layout (location = 0) in vec3 aPos;
// Normals 
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture Coordinates
layout (location = 3) in vec2 aTex;

// Outputs the current position for the Fragment Shader
out vec3 crntPos;
// Outputs the normal for the Fragment Shader
out vec3 Normal;
// Outpus the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates for the Fragment Shader
out vec2 texCoord;

// Imports the camera matrix from the main function
uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;


void main()
{
    // Calculates current position
    crntPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0f));
    // Assigns the normal from the Vertex Data to "Normal"
    Normal = aNormal;
    // Assigns the colors from the Vertex Data to "Colors"
    color = aColor;
    // Assigns the texture coordinates from the Vertex Data to "texCoord"
    texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;
    
    // Outputs the positions/coordinates of all vertices
    gl_Position = camMatrix * vec4(crntPos, 1.0);
}
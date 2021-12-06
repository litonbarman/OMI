#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// lighting
out vec3 FragPos;
out vec3 Normal;

void main()
{
    TexCoords = aTexCoords;    
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    // lighting
    FragPos = vec3( model * vec4(aPos, 1.0));  //   only model * vec4(aPos, 1.0)
    Normal = vec3( mat4(model) * vec4(aNormal, 0.0));   // my own method

}
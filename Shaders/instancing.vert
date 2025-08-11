#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in mat4 aInstanceMatrix;

out vec2 TexCoords; 
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model; 
uniform mat4 projection;
uniform mat4 view;

void main() 
{

    TexCoords = aTexCoords;
    Normal = normalize(mat3(transpose(inverse(aInstanceMatrix))) * aNormal); //world space
    vec4 worldPos = aInstanceMatrix * vec4(aPos, 1.0f);
    FragPos = vec3(worldPos); 
    gl_Position = projection * view * aInstanceMatrix * vec4(aPos, 1.0f); 
} 
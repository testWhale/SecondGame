#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

out vec3 color;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform float scale;
uniform mat4 model;
uniform mat3 normalMat;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec3 scaledPos = aPos + aPos * scale;
    vec4 worldPos = model * vec4(scaledPos, 1.0);
   gl_Position = projection * view * worldPos;
   Normal = normalize(mat3(model) * aNormal); //world space

   TexCoord = aTexCoord;
   FragPos = vec3(worldPos);  //world space
  
}
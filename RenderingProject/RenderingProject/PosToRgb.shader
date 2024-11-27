#vertexshader
#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;

out vec2 texCoord;
out vec4 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    position = projection * view * model * vec4(Position.x, Position.y, Position.z, 1.0);
}

#fragmentshader
#version 330 core
in vec4 position;
out vec4 FragColor;

void main()
{
    FragColor = position;
}
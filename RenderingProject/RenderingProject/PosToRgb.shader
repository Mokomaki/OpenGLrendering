#vertexshader
#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;

out vec2 texCoord;
out vec4 position;

void main()
{
    gl_Position = vec4(Position.x, Position.y, Position.z, 1.0);
    position = vec4(Position.x, Position.y, Position.z, 1.0);
}

#fragmentshader
#version 330 core
in vec4 position;
out vec4 FragColor;

void main()
{
    FragColor = position;
}
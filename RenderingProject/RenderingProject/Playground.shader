#vertexshader
#version 330 core

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;

out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(Position.x, Position.y, Position.z, 1.0);
}

#fragmentshader
#version 330 core

out vec4 FragColor;

uniform float color;

void main()
{
    FragColor = vec4(max(color,1.0f), max(color, 0.5f), max(color, 0.2f), max(color, 1.0f));
}
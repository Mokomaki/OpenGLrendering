#vertexshader
#version 330 core
layout(location = 0) in vec3 Position;

uniform mat4 lightspacematrix;
uniform mat4 model;

void main()
{
    gl_Position = lightspacematrix * model * vec4(Position, 1.0);
}

#fragmentshader
#version 330 core

void main()
{
}
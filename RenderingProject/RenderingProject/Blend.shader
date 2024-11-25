#vertexshader
#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 TexCoord;

out vec2 texCoord;

void main()
{
    gl_Position = vec4(Position.x, Position.y, Position.z, 1.0);
    texCoord = TexCoord;
}

#fragmentshader
#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D Utexture0;
uniform sampler2D Utexture1;

void main()
{
    FragColor = mix(texture(Utexture0, texCoord), texture(Utexture1, texCoord), 0.34);
}
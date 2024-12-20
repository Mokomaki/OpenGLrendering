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
    texCoord = TexCoord;
}

#fragmentshader
#version 330 core

out vec4 FragColor;
in vec2 texCoord;

uniform sampler2D Utexture0;

void main()
{
    vec4 texcolor = texture(Utexture0, texCoord);
    
    if (texcolor.a < 0.05f)
        discard;

    FragColor = texcolor;
}
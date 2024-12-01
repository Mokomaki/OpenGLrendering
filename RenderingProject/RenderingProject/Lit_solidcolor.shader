#vertexshader
#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 2) in vec3 Normal;

out vec3 normalvalue;
out vec3 fragposition;

uniform mat3 modelinversetransposed;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(Position.x, Position.y, Position.z, 1.0);
    fragposition = vec3(model * vec4(Position, 1.0));
    normalvalue = modelinversetransposed * Normal;
}

#fragmentshader
#version 330 core

out vec4 FragColor;

in vec3 fragposition;
in vec3 normalvalue;

uniform vec3 cameraposition;
uniform vec3 lightcolor;
uniform vec3 color;
uniform vec3 lightposition;

void main()
{
    vec3 norm = normalize(normalvalue);
    vec3 lightDir = normalize(lightposition - fragposition);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightcolor;

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightcolor;

    float specularStrength = 0.5;

    vec3 viewDir = normalize(cameraposition - fragposition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightcolor;

    vec3 result = (ambient + diffuse + specular) * color;
    FragColor = vec4(result, 1.0);
}
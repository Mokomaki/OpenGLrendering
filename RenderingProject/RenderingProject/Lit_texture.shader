#vertexshader
#version 330 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 TexCoord;
layout(location = 2) in vec3 Normal;

out vec2 texcoord;
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
    texcoord = TexCoord;
}

#fragmentshader
#version 330 core

struct DirectionalLight {
    vec3 lightdirection;
    vec3 lightcolor;
};

struct PointLight {
    vec3 position;
    vec3 color;
    float constantterm;
    float linearterm;
    float quadraticterm;
};

out vec4 FragColor;
in vec3 fragposition;
in vec3 normalvalue;
in vec2 texcoord;

#define MAX_DIR_LIGHTS 4
#define MAX_POINT_LIGHTS 8

uniform DirectionalLight directionallights[MAX_DIR_LIGHTS];
uniform PointLight pointlights[MAX_POINT_LIGHTS];
uniform int directionallightcount;
uniform int pointlightcount;
uniform vec3 cameraposition;

uniform vec3 u_ambient;
uniform sampler2D u_diffuse;
uniform sampler2D u_specular;
uniform float u_smoothness;

vec3 CalculateDirectionalLightContribution(DirectionalLight light, vec3 normal, vec3 viewdir);
vec3 CalculatePointLightContribution(PointLight light, vec3 normal, vec3 fragpos, vec3 viewdir);

void main()
{

    vec3 norm = normalize(normalvalue);
    vec3 viewdirection = normalize(cameraposition - fragposition);
    vec3 result = vec3(0.0);

    for (int i = 0; i < directionallightcount; i++)
    {
        result += CalculateDirectionalLightContribution(directionallights[i], norm, viewdirection);
    }
    for (int i = 0; i < pointlightcount; i++)
    {
        result += CalculatePointLightContribution(pointlights[i], norm, fragposition, viewdirection);
    }

    //FragColor = texture(u_diffuse, texcoord);
    FragColor = vec4(result, 1.0);
}

vec3 CalculatePointLightContribution(PointLight light, vec3 normal, vec3 fragpos, vec3 viewdir)
{
    vec3 lightDir = normalize(light.position - fragpos);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewdir, reflectDir), 0.0), u_smoothness);

    float distance = length(light.position - fragpos);
    float attenuation = 1.0 / (light.constantterm + light.linearterm * distance + light.quadraticterm * (distance * distance));

    vec3 ambient = light.color * u_ambient * vec3(texture(u_diffuse, texcoord));
    vec3 diffuse = light.color * diff * vec3(texture(u_diffuse, texcoord));
    vec3 specular = light.color * spec * vec3(texture(u_specular, texcoord));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalculateDirectionalLightContribution(DirectionalLight light, vec3 normal, vec3 viewdir)
{
    vec3 lightDir = normalize(-light.lightdirection);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewdir, reflectDir), 0.0), u_smoothness);

    vec3 ambient = light.lightcolor * u_ambient * vec3(texture(u_diffuse, texcoord));
    vec3 diffuse = light.lightcolor * diff * vec3(texture(u_diffuse, texcoord));
    vec3 specular = light.lightcolor * spec * vec3(texture(u_specular, texcoord));
    return (ambient + diffuse + specular);
}
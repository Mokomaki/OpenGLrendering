#include "Scene.h"

void Scene::Initialize()
{
    m_camera = new Camera(glm::vec3(0.0f, 1.8f, 3.0f));
    
    m_assets["lit_texture"] = new Shader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Lit_texture.shader", true);
    m_assets["lit_solidcolor"] = new Shader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Lit_solidcolor.shader", true);
    m_assets["playgroundshader"] = new Shader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Playground.shader", true);
    m_assets["UVcube"] = new Mesh("D:/Documents/cube.obj");
    m_assets["suzannemesh"] = new Mesh("D:/Documents/Suzanne.obj");
    m_assets["planemesh"] = new Mesh("D:/Documents/plane.obj");
    m_assets["moonbaboon"] = new Texture("D:/Pictures/MOONBABOON.png");
    PbrProperties testboxprops = { glm::vec3(0.1f,0.1f,0.12f),glm::vec3(0.954f,0.746f,0.32f),glm::vec3(1.0f,1.0f,1.0f),128.0f };
    m_uniformdata["testmaterial"] = new UniformData("testmaterial", testboxprops);
    PbrProperties groundprops = { glm::vec3(0.1f,0.1f,0.1f),glm::vec3(0.137,0.141f,0.169f),glm::vec3(0.1f,0.1f,0.1f),16.0f };
    m_uniformdata["groundmaterial"] = new UniformData("groundmaterial", groundprops);

    CreateLightDirectional(glm::vec3(3.0f, -1.0f, -3.5f), glm::vec3(1.0f, 1.0f, 1.0f));
    CreateLightPoint(glm::vec3(-5.0f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 100);
    CreateLightPoint(glm::vec3(5.0f, 2.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 200);
    CreateLightPoint(glm::vec3(0.0f, 1.0f, -15.0f), glm::vec3(0.0f, 1.0f, 0.0f), 600);

    WorldObject& groundplane = CreateWorldObect("ground");
    groundplane.m_transform = glm::scale(groundplane.m_transform, glm::vec3(15.0f, 1.0f, 15.0f));
    groundplane.m_transform = glm::translate(groundplane.m_transform, glm::vec3(0.0f, -1.5f, 0.0f));
    groundplane.AssociateWithAsset("playgroundshader");
    groundplane.AssociateWithAsset("planemesh");
    groundplane.AssociateWithUniform("groundmaterial");


    for (int i = 0; i < 10; i++)
    {
        WorldObject& cube = CreateWorldObect("cube");
        cube.AssociateWithAsset("playgroundshader");
        cube.AssociateWithAsset("UVcube");
        cube.AssociateWithUniform("testmaterial");
        cube.m_transform = glm::translate(cube.m_transform, glm::vec3(((i-5) * 3), 0.0f, -10.0f));
    }

    WorldObject& suzanne = CreateWorldObect("suzanne");
    suzanne.AssociateWithAsset("playgroundshader");
    suzanne.AssociateWithAsset("suzannemesh");
    suzanne.AssociateWithUniform("testmaterial");
}

WorldObject* Scene::GetWorldObjectByName(const char* name)
{
    for (auto& object : m_objects)
    {
        if (strcmp(object.m_name, name) == 0)
            return &object;
    }
}
std::vector<WorldObject*> Scene::GetWorldObjectsWithName(const char* name)
{
    std::vector<WorldObject*> out;
    for (auto& object : m_objects)
    {
        if (strcmp(object.m_name, name) == 0)
            out.push_back(&object);
    }
    return out;
}
WorldObject& Scene::CreateWorldObect(const char* name)
{
    m_objects.emplace_back(name);
    return m_objects.back();
}
DirectionalLight& Scene::CreateLightDirectional(glm::vec3 direction, glm::vec3 color)
{
    m_directionalLights.emplace_back(direction, color);
    return m_directionalLights.back();
}
PointLight& Scene::CreateLightPoint(glm::vec3 position, glm::vec3 color, float range)
{
    m_pointLights.emplace_back(position, color, range);
    return m_pointLights.back();
}
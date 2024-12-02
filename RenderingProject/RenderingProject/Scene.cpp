#include "Scene.h"

void Scene::Initialize()
{
    m_camera = new Camera(glm::vec3(0.0f, 1.8f, 3.0f));
    
    m_assets["unlit_texture"] = new Shader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Unlit_texture.shader", false);
    m_assets["lit_texture"] = new Shader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Lit_texture.shader", true);
    m_assets["lit_solidcolor"] = new Shader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Lit_solidcolor.shader", true);
    m_assets["UVcube"] = new Mesh("D:/Documents/cube.obj");
    m_assets["suzannemesh"] = new Mesh("D:/Documents/Suzanne.obj");
    m_assets["planemesh"] = new Mesh("D:/Documents/plane.obj");
    m_assets["moonbaboon"] = new Texture("D:/Pictures/MOONBABOON.png");

    CreateLight(glm::vec3(-7.0f, 4.0f, 2.5f), glm::vec3(1.0f, 1.0f, 1.0f));

    WorldObject& groundplane = CreateWorldObect("ground");
    groundplane.m_transform = glm::scale(groundplane.m_transform, glm::vec3(15.0f, 1.0f, 15.0f));
    groundplane.m_transform = glm::translate(groundplane.m_transform, glm::vec3(0.0f, -1.5f, 0.0f));
    groundplane.AssociateWithAsset("lit_solidcolor");
    groundplane.AssociateWithAsset("planemesh");
    m_uniformdata["groundcolor"] = new UniformData("color", glm::vec3(0.125f, 0.125f, 0.125f));
    groundplane.AssociateWithUniform("groundcolor");

    for (int i = 0; i < 10; i++)
    {
        WorldObject& cube = CreateWorldObect("cube");
        cube.AssociateWithAsset("unlit_texture");
        cube.AssociateWithAsset("UVcube");
        cube.AssociateWithAsset("moonbaboon");
        cube.m_transform = glm::translate(cube.m_transform, glm::vec3(((i-5) * 3), 0.0f, -10.0f));
    }

    WorldObject& suzanne = CreateWorldObect("suzanne");
    suzanne.AssociateWithAsset("lit_texture");
    suzanne.AssociateWithAsset("moonbaboon");
    suzanne.AssociateWithAsset("suzannemesh");
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
Light& Scene::CreateLight(glm::vec3 position, glm::vec3 color)
{
    m_lights.emplace_back(position, color);
    return m_lights.back();
}
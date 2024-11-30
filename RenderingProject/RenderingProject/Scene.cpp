#include "Scene.h"

void Scene::Initialize()
{
    m_camera = new Camera(glm::vec3(0.0f, 1.8f, 3.0f));
    
    m_assets["textureshader"] = new Shader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Unlit_texture.shader");
    m_assets["UVcube"] = new Mesh("D:/Documents/cube.obj");
    m_assets["moonbaboon"] = new Texture("D:/Pictures/MOONBABOON.png");

    for (int i = 0; i < 10; i++)
    {
        m_objects.emplace_back("moonbaboon", "UVcube", "textureshader", "cube");
        m_objects[i].m_transform = glm::translate(m_objects[i].m_transform, glm::vec3((i * 3), 0.0f, -10.0f));
    }
    
    m_assets["solidshader"] = new Shader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Lit.shader");
    m_assets["suzannemesh"] = new Mesh("D:/Documents/Suzanne.obj");
    const char* suzanneassets[] = { "solidshader", "suzannemesh" };
    m_objects.emplace_back(suzanneassets,2, "suzanne");
    m_uniformdata["suzannecolor"] = new UniformData("color", glm::vec3(1.0f, 1.0f, 1.0f));
    GetWorldObjectByName("suzanne")->AssociateWithUniform("suzannecolor");

    m_uniformdata["lightcolor"] = new UniformData("lightcolor", glm::vec3(0.769f, 0.498f, 0.165f));
    m_uniformdata["lightposition"] = new UniformData("lightposition", glm::vec3(-7.0f, 4.0f, 2.5f));
    m_uniformdata["cameraposition"] = new UniformData("cameraposition", m_camera->Position);
    GetWorldObjectByName("suzanne")->AssociateWithUniform("lightcolor");
    GetWorldObjectByName("suzanne")->AssociateWithUniform("lightposition");
    GetWorldObjectByName("suzanne")->AssociateWithUniform("cameraposition");

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
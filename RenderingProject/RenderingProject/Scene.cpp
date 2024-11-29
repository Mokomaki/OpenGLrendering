#include "Scene.h"

void Scene::Initialize()
{
    m_camera = new Camera(glm::vec3(0.0f, 1.8f, 3.0f));
    
    m_assets["textureshader"] = new Shader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Unlit_texture.shader");
    m_assets["UVcube"] = new Mesh("D:/Documents/CubeUVS.obj", false);
    m_assets["moonbaboon"] = new Texture("D:/Pictures/MOONBABOON.png");

    for (int i = 0; i < 10; i++)
    {
        m_objects.emplace_back(new WorldObject("moonbaboon", "UVcube", "textureshader", "cube"));
        m_objects[i]->m_transform = glm::translate(m_objects[i]->m_transform, glm::vec3((i * 3), 0.0f, -10.0f));
    }
    
    m_assets["solidshader"] = new Shader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Unlit_solidcolor.shader");
    m_assets["suzanne"] = new Mesh("D:/Documents/Suzanne.obj", false);
    m_assets["vaderTex"] = new Texture("D:/Pictures/Wallpapers/vader.jpg");
    m_objects.emplace_back(new WorldObject("suzanne", "vaderTex", "solidshader", "suzanne"));

    m_assets["suzannecolor"] = new UniformData("color", glm::vec3(0.769f, 0.498f, 0.165f));

    GetWorldObjectByName("suzanne")->m_assets.emplace_back("suzannecolor");
}

WorldObject* Scene::GetWorldObjectByName(const char* name)
{
    for (auto object : m_objects)
    {
        if (strcmp(object->m_name, name) == 0)
            return object;
    }
}
std::vector<WorldObject*> Scene::GetWorldObjectsWithName(const char* name)
{
    std::vector<WorldObject*> out;
    for (auto object : m_objects)
    {
        if (strcmp(object->m_name, name) == 0)
            out.push_back(object);
    }
    return out;
}
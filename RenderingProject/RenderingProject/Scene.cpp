#include "Scene.h"

void Scene::Initialize()
{
    m_camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    m_cameraProjection = glm::perspective(glm::radians(80.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    //m_cameraView = glm::mat4(1.0f);
    //m_cameraView = glm::translate(m_cameraView, glm::vec3(0.0f, 0.0f, -3.0f));

    m_assets.push_back(new Asset("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Image.shader", m_assets.size()));
    m_assets.push_back(new Asset("D:/Documents/CubeUVS.obj", false, m_assets.size()));
    //m_assets.push_back(new Asset(PrimitiveMeshShapes::CUBE_MESH, m_assets.size()));
    const char* textures[] = { "D:/Pictures/MOONBABOON.png" };
    m_assets.push_back(new Asset(textures, m_assets.size(), 1));
    unsigned int assets[3] = { 0,1,2 };
    for (int i = 0; i < 10; i++)
    {
        m_objects.push_back(new WorldObject(assets,3,"cube"));
        m_objects[i]->m_transform = glm::translate(m_objects[i]->m_transform, glm::vec3((i * 3), 0.0f, -10.0f));
    }
    
    m_assets.push_back(new Asset("D:/Documents/Suzanne.obj", false, m_assets.size()));
    //m_assets.push_back(new Asset(PrimitiveMeshShapes::CUBE_MESH, m_assets.size()));
    const char* textures2[] = { "D:/Pictures/Wallpapers/vader.jpg" };
    m_assets.push_back(new Asset(textures2, m_assets.size(), 1));
    unsigned int assets2[3] = { 0,3,4 };
    m_objects.push_back(new WorldObject(assets2, 3, "suzanne"));
    
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
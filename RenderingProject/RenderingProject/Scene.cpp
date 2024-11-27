#include "Scene.h"

void Scene::Initialize()
{
    m_cameraProjection = glm::perspective(glm::radians(80.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    m_cameraView = glm::mat4(1.0f);
    m_cameraView = glm::translate(m_cameraView, glm::vec3(0.0f, 0.0f, -3.0f));

    m_assets.push_back(new Asset("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Image.shader",m_assets.size()));
    m_assets.push_back(new Asset(PrimitiveMeshShapes::CUBE_MESH, m_assets.size()));
    const char* textures[] = { "D:/Pictures/MOONBABOON.png" };
    m_assets.push_back(new Asset(textures, m_assets.size(), 1));
    unsigned int assets[3] = {0,1,2};
    for (int i = 0; i < 1; i++)
    {
        m_objects.push_back(new WorldObject(assets,3));
    }
}
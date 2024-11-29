#include "Renderer.h"

Renderer::Renderer()
{
    m_clearColor = glm::vec4(0.17254901f, 0.17254901f, 0.17254901f, 1.0f);
    m_clearflags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
}

void Renderer::Render(Scene* scene)
{
    Clear();

    glm::mat4 viewMatrix = scene->m_camera->GetViewMatrix();

    glm::vec3 myColor = glm::vec3(1.0f, 1.0f, 1.0f);
    std::set<Asset*> boundAssets;
    for (int object = 0; object < scene->m_objects.size(); object++)
    {

        unsigned int indexCount = 0;
        Asset* shaderAsset = nullptr;
        for (int asset = 0; asset < scene->m_objects[object]->m_assets.size(); asset++)
        {
            Asset* currentAsset = scene->m_assets[scene->m_objects[object]->m_assets[asset]];

            if (boundAssets.find(currentAsset) == boundAssets.end())
            {
                currentAsset->Bind();
                boundAssets.clear();
                boundAssets.insert(currentAsset);
            }

            if (currentAsset->GetAssetType() == AssetType::SHADER)
            {
                shaderAsset = currentAsset;
            }
            else if (currentAsset->GetAssetType() == AssetType::MESH)
            {
                indexCount = currentAsset->GetIndexCount();
            }
        }
        shaderAsset->SetUniformData("color", myColor);
        shaderAsset->SetTransformation(scene->m_objects[object]->m_transform,viewMatrix,scene->m_camera->m_Projection);
        Draw(indexCount);
    }
}

void Renderer::Draw(unsigned int indexCount)
{
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}

void Renderer::Clear()
{
    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
    glClear(m_clearflags);
}
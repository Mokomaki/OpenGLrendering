#include "MeshRenderer.h"

void MeshRenderer::Render(Scene* scene)
{
    glm::vec3 myColor = glm::vec3(1.0f, 1.0f, 1.0f);

    glClearColor(0.17254901f, 0.17254901f, 0.17254901f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 viewMatrix = scene->m_camera->GetViewMatrix();
    for (int object = 0; object < scene->m_objects.size(); object++)
    {

        unsigned int indexCount = 0;
        Asset* shaderAsset = nullptr;
        for (int asset = 0; asset < scene->m_objects[object]->m_assets.size(); asset++)
        {
            Asset* currentAsset = scene->m_assets[scene->m_objects[object]->m_assets[asset]];

            currentAsset->Bind();

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
        shaderAsset->SetTransformation(scene->m_objects[object]->m_transform,viewMatrix,scene->m_cameraProjection);
        Draw(indexCount);
    }
}

void MeshRenderer::Draw(unsigned int indexCount)
{
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
#include "MeshRenderer.h"

void MeshRenderer::Render(Scene* scene)
{
    glm::vec3 myColor = glm::vec3(0.8f, 0.1f, 0.3f);

    glClearColor(0.17254901f, 0.17254901f, 0.17254901f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (int object = 0; object < scene->m_objects.size(); object++)
    {
        unsigned int indexCount = 0;
        Asset* shaderAsset = nullptr;
        for (int asset = 0; asset < scene->m_objects[object]->m_assets.size(); asset++)
        {
            scene->m_assets[asset]->Bind();

            if (scene->m_assets[asset]->GetAssetType() == AssetType::SHADER)
            {
                shaderAsset = scene->m_assets[asset];
            }
            else if (scene->m_assets[asset]->GetAssetType() == AssetType::MESH)
            {
                indexCount = scene->m_assets[asset]->GetIndexCount();
            }
        }
        shaderAsset->SetUniformData("color", myColor);
        shaderAsset->SetTransformation(scene->m_objects[object]->m_transform,scene->m_cameraView,scene->m_cameraProjection);
        Draw(indexCount);
    }
}

void MeshRenderer::Draw(unsigned int indexCount)
{
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
}
/*
void MeshRenderer::SetShaderUniformFloat(const std::string& name, float value)
{
    m_shader->Bind();
    m_shader->SetUniformFloat(name, value);
}
void MeshRenderer::SetShaderUniformInt(const std::string& name, int value)
{
    m_shader->Bind();
    m_shader->SetUniformInt(name, value);
}
void MeshRenderer::SetShaderUniformBool(const std::string& name, bool value)
{
    m_shader->Bind();
    m_shader->SetUniformBool(name, value);
}
void MeshRenderer::SetTransformation(glm::mat4& transfrorm)
{
    m_shader->Bind();
    m_shader->SetUniformTransfrom(transfrorm);
}*/

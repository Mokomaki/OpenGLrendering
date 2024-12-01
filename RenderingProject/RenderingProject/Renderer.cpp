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

    for (int object = 0; object < scene->m_objects.size(); object++)
    {
        Mesh* meshAsset = nullptr;
        Shader* shaderAsset = nullptr;

        for (const char* assetname : scene->m_objects[object].m_assets)
        {
            Asset* currentAsset = scene->m_assets[assetname];
            currentAsset->Bind();
            switch (currentAsset->GetAssetType())
            {
                case ASSETTYPE::SHADER:
                    shaderAsset = (Shader*)currentAsset;
                    break;
                case ASSETTYPE::MESH:
                    meshAsset = (Mesh*)currentAsset;
                    break;
            default:
                break;
            }
        }

        for (const char* uniformscenename : scene->m_objects[object].m_uniformData)
        {
            UniformData* uniformptr = scene->m_uniformdata[uniformscenename];

            switch (uniformptr->GetUniformType())
            {
            case UNIFORMDATATYPE::BOOL:
                bool bvalue;
                uniformptr->GetUniformValue(bvalue);
                shaderAsset->SetUniform(uniformptr->GetUniformName(), bvalue);
                break;
            case UNIFORMDATATYPE::INT:
                int ivalue;
                uniformptr->GetUniformValue(ivalue);
                shaderAsset->SetUniform(uniformptr->GetUniformName(), ivalue);
                break;
            case UNIFORMDATATYPE::FLOAT:
                float fvalue;
                uniformptr->GetUniformValue(fvalue);
                shaderAsset->SetUniform(uniformptr->GetUniformName(), fvalue);
                break;
            case UNIFORMDATATYPE::VEC3:
                glm::vec3 v3value;
                uniformptr->GetUniformValue(v3value);
                shaderAsset->SetUniform(uniformptr->GetUniformName(), v3value);
                break;
            case UNIFORMDATATYPE::MAT4:
                glm::mat4 m4value;
                uniformptr->GetUniformValue(m4value);
                shaderAsset->SetUniform(uniformptr->GetUniformName(), m4value);
                break;
            default:
                break;
            }
        }

        if (shaderAsset == nullptr)
        {
            std::cout << "ERROR: Attempted to draw object without a shader!" << std::endl;
            continue;
        }

        if (shaderAsset->IsLitShader())
        {
            glm::mat3 inverseTransposedModel;
            inverseTransposedModel = glm::inverse(scene->m_objects[object].m_transform);
            inverseTransposedModel = glm::transpose(inverseTransposedModel);
            shaderAsset->SetUniform("modelinversetransposed", inverseTransposedModel);
        }

        shaderAsset->SetUniformTransfrom(scene->m_objects[object].m_transform,viewMatrix,scene->m_camera->m_Projection);
        Draw(meshAsset->GetIndexCount());
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
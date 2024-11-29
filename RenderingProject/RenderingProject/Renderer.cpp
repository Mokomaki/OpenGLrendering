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
    for (int object = 0; object < scene->m_objects.size(); object++)
    {
        Mesh* meshAsset = nullptr;
        Shader* shaderAsset = nullptr;

        std::vector<UniformData*> uniforms;

        for (const char* assetname : scene->m_objects[object]->m_assets)
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
                case ASSETTYPE::UNIFORMDATA:
                    uniforms.push_back((UniformData*)currentAsset);
            default:
                break;
            }
        }

        for (UniformData* uniform : uniforms)
        {
            switch (uniform->GetUniformType())
            {
            case UNIFORMDATATYPE::BOOL:
                bool bvalue;
                uniform->GetUniformValue(bvalue);
                shaderAsset->SetUniform(uniform->m_name, bvalue);
                break;
            case UNIFORMDATATYPE::INT:
                int ivalue;
                uniform->GetUniformValue(ivalue);
                shaderAsset->SetUniform(uniform->m_name, ivalue);
                break;
            case UNIFORMDATATYPE::FLOAT:
                float fvalue;
                uniform->GetUniformValue(fvalue);
                shaderAsset->SetUniform(uniform->m_name, fvalue);
                break;
            case UNIFORMDATATYPE::VEC3:
                glm::vec3 v3value;
                uniform->GetUniformValue(v3value);
                shaderAsset->SetUniform(uniform->m_name, v3value);
                break;
            case UNIFORMDATATYPE::MAT4:
                glm::mat4 m4value;
                uniform->GetUniformValue(m4value);
                shaderAsset->SetUniform(uniform->m_name, m4value);
                break;
            default:
                break;
            }
        }

        shaderAsset->SetUniformTransfrom(scene->m_objects[object]->m_transform,viewMatrix,scene->m_camera->m_Projection);
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
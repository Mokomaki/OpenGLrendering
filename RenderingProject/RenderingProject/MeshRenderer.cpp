#include "MeshRenderer.h"

void MeshRenderer::Initialize(Mesh* mesh, Shader* shader)
{
    m_mesh = mesh;
    m_shader = shader;

    glGenVertexArrays(1, &m_vertexArrayID);
    glGenBuffers(1, &m_vertexBufferID);
    glGenBuffers(1, &m_elementBufferID);
    glBindVertexArray(m_vertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_mesh->GetVertexCount(), m_mesh->GetVertices(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_mesh->GetIndexCount(), m_mesh->GetIndices(), GL_STATIC_DRAW);

    //Vertex layout
    //CURRENT VERTEX STRIDE: 5 * FLOAT
    //Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)0);
    glEnableVertexAttribArray(0);
    //UV attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float)*5, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void MeshRenderer::SetTexture(Texture* texture)
{
    if (m_textures.size() < 16)
    {
        std::stringstream textureName;
        textureName << "Utexture" << m_textures.size();
        
        m_shader->Bind();
        m_shader->SetUniformInt(textureName.str(), m_textures.size());
        m_textures.push_back(*texture);
    }
    else
    {
        std::cout << "ERROR: Maximum of 16 textures can be loaded at once!" << std::endl;
    }
}

void MeshRenderer::Draw()
{
    for (int i = 0; i < m_textures.size(); i++)
    {
        m_textures[i].Bind(i);
    }
    m_shader->Bind();
    glBindVertexArray(m_vertexArrayID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBufferID);
    glDrawElements(GL_TRIANGLES, m_mesh->GetIndexCount(), GL_UNSIGNED_INT, 0);
}

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
}
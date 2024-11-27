#include "MeshRenderer.h"

void MeshRenderer::Initialize()
{

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

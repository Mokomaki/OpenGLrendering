#include "Shader.h"

Shader::Shader(const char* path)
{
    GenerateShader(path);
}

ASSETTYPE Shader::GetAssetType()
{
    return ASSETTYPE::SHADER;
}

void Shader::GenerateShader(const char * path)
{
    LoadShaderFromFile(path);
    const char* vertexSource = m_vertexSource.c_str();
    const char* fragmentSource = m_fragmentSource.c_str();

    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShaderID, 1, &vertexSource, NULL);
    glCompileShader(m_vertexShaderID);
    CheckShaderError(m_vertexShaderID, GL_COMPILE_STATUS);

    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShaderID, 1, &fragmentSource, NULL);
    glCompileShader(m_fragmentShaderID);
    CheckShaderError(m_fragmentShaderID, GL_COMPILE_STATUS);

    //Shader program
    m_programID = glCreateProgram();
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);
    glLinkProgram(m_programID);
    
    CheckShaderError(m_programID, GL_LINK_STATUS);

    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
    
    m_isInitialized = true;
    glUseProgram(m_programID);
    m_modelUnifromLocation = glGetUniformLocation(m_programID, "model");
    m_viewUnifromLocation = glGetUniformLocation(m_programID, "view");
    m_projectionUnifromLocation = glGetUniformLocation(m_programID, "projection");

}

unsigned int Shader::GetUniformLocation(const std::string& name) const
{
    if (m_uniformLocations.find(name) != m_uniformLocations.end())
        return m_uniformLocations[name];

    m_uniformLocations[name] = glGetUniformLocation(m_programID, name.c_str());
    return m_uniformLocations[name];
}

void Shader::SetUniform(const std::string& name, glm::mat4& value)
{
    glUniformMatrix4fv(GetUniformLocation(name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::SetUniform(const std::string& name, glm::vec3& value)
{
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void Shader::SetUniform(const std::string& name, float value)
{
    glUniform1f(GetUniformLocation(name.c_str()), value);
}

void Shader::SetUniform(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name.c_str()), value);
}

void Shader::SetUniform(const std::string& name, bool value)
{
    glUniform1i(GetUniformLocation(name.c_str()), (int)value);
}

void Shader::SetUniformTransfrom(glm::mat4& model, glm::mat4& view, glm::mat4& projection)
{
    glUniformMatrix4fv(m_modelUnifromLocation, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(m_viewUnifromLocation, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(m_projectionUnifromLocation, 1, GL_FALSE, glm::value_ptr(projection));
}

void Shader::Bind()
{
    glUseProgram(m_programID);
}

bool Shader::IsInitialized()
{
    return m_isInitialized;
}

void Shader::CheckShaderError(unsigned int shaderID, GLenum process)
{
    int  success;
    char infoLog[512];

    if (process == GL_COMPILE_STATUS)
    {
        glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << std::endl << "Shaderprogram id:" << std::endl << shaderID << std::endl << infoLog << std::endl;
            glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
        }
    }
    else
    {
        glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shaderID, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << std::endl << "Shaderprogram id:" << std::endl << shaderID << std::endl << infoLog << std::endl;
        }
    }

}

void Shader::LoadShaderFromFile(const char* path)
{

    std::ifstream stream(path);
    std::string line;
    std::stringstream vertexSource;
    std::stringstream fragmentSource;
    
    bool isVertex = true;

    while (std::getline(stream, line))
    {
        if (line.find("#vertexshader") != std::string::npos)
        {
            isVertex = true;
        }
        else if (line.find("#fragmentshader") != std::string::npos)
        {
            isVertex = false;

        }
        else
        {
            if (isVertex)
            {
                vertexSource << line << std::endl;
            }
            else
            {
                fragmentSource << line << std::endl;
            }
        }
    }
    m_fragmentSource = fragmentSource.str();
    m_vertexSource = vertexSource.str();
}

Shader::~Shader()
{
    glDeleteProgram(m_programID);
}
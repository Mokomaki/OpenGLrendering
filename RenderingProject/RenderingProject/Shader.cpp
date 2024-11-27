#include "Shader.h"

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
    //m_viewUnifromLocation = glGetUniformLocation(m_programID, "view");
    //m_projectionUnifromLocation = glGetUniformLocation(m_programID, "projection");

}

void Shader::SetUniformFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
}
void Shader::SetUniformInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
}
void Shader::SetUniformBool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
}
void Shader::SetUniformTransfrom(glm::mat4 transform)
{
    glUniformMatrix4fv(m_modelUnifromLocation, 1, GL_FALSE, glm::value_ptr(transform));
}
void Shader::Bind()
{
    if (!m_isInitialized)
        std::cout << "ERROR: Attempted to bind uninitialized shaderprogram!" << std::endl;

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
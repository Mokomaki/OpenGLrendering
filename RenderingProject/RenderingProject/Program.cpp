#pragma once
#include "Program.h"


void Program::Run() 
{
    Initialize();
    m_scene.Initialize();
    RunApplicationLoop();
}

void Program::RunApplicationLoop()
{
    while (!glfwWindowShouldClose(m_window))
    {
        ProcessInput();
        Render();

        m_scene.m_objects[0]->m_transform = glm::rotate(m_scene.m_objects[0]->m_transform,glm::radians(2.0f),  glm::vec3(0.0, 0.0, 0.0005f));


        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void Program::Render()
{
    glClearColor(0.17254901f, 0.17254901f, 0.17254901f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int object = 0; object < m_scene.m_objects.size(); object++)
    {
        Asset* shaderAsset = nullptr;
        unsigned int indexCount = 0;
        for (int asset = 0; asset < m_scene.m_objects[object]->m_assets.size(); asset++)
        {
            m_scene.m_assets[asset]->Bind();
            if (m_scene.m_assets[asset]->GetAssetType() == AssetType::SHADER)
                shaderAsset = m_scene.m_assets[asset];
            if (m_scene.m_assets[asset]->GetAssetType() == AssetType::MESH)
                indexCount = m_scene.m_assets[asset]->GetIndexCount();
        }
        shaderAsset->SetTransformation(m_scene.m_objects[object]->m_transform);
        m_renderer.Draw(indexCount);
    }
    

}

void Program::ProcessInput()
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        std::cout << "ESCAPE PRESSED" << std::endl;
        //m_renderers[0].SetShaderUniformFloat("color", 1.0f);
    }
    else
    {
        //m_renderers[0].SetShaderUniformFloat("color", 0.0f);
    }
}

void Program::Initialize()
{
    //=====Initilize window=====
    
    //Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    //Make a window
    m_window = glfwCreateWindow(800, 600, "RendererProgram", NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    else
    {
        glfwMakeContextCurrent(m_window);
    }

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }

    //=====Initilize OpenGl=====

    //Set viewport and a callback for window resize
    glViewport(0, 0, 800, 600);
    void FramebufferSizeCallback(GLFWwindow * window, int width, int height);
    glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
}
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
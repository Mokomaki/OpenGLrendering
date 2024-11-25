#pragma once
#include "Program.h"


void Program::Run() 
{
    Initialize();

    MeshRenderer myRenderer;
    Shader myShader;
    Mesh myMesh;
    Texture myTexture;
    
    myTexture.Initialize("D:/Pictures/MOONBABOON.png",GL_CLAMP_TO_BORDER);
    myMesh.CreatePrimitive(PrimitiveMeshShapes::TRIANGLE_MESH);
    myShader.GenerateShader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Image.shader");

    myRenderer.Initialize(&myMesh, &myShader);
    myRenderer.SetTexture(&myTexture);

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    myRenderer.SetTransformation(transform);

    m_renderers.push_back(myRenderer);


    RunApplicationLoop();
}

void Program::RunApplicationLoop()
{
    while (!glfwWindowShouldClose(m_window))
    {
        ProcessInput();
        Render();


        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void Program::Render()
{
    glClearColor(0.17254901f, 0.17254901f, 0.17254901f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < m_renderers.size(); i++)
    {
        m_renderers[i].Draw();
    }
    
}

void Program::ProcessInput()
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        std::cout << "ESCAPE PRESSED" << std::endl;
        m_renderers[0].SetShaderUniformFloat("color", 1.0f);
    }
    else
    {
        m_renderers[0].SetShaderUniformFloat("color", 0.0f);
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
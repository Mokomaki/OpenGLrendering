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

    int prevWidth = 0, prevHeight = 0;
    auto t_start = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(m_window))
    {
        //Handle window resize
        int width = 0, height =0;
        glfwGetWindowSize(m_window, &width, &height);
        if (width != prevWidth || height != prevHeight)
        {
            m_scene.m_cameraProjection = glm::perspective(glm::radians(80.0f), (float)width / (float)height, 0.1f, 100.0f);
        }
        //Timing
        auto t_now = std::chrono::high_resolution_clock::now();
        m_deltatime = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
        t_start = t_now;
        //std::cout <<  1 / m_deltatime << std::endl;

        ProcessInput();

        float i = 1;
        for (auto obj : m_scene.m_objects)
        {
            float rotation = i * m_deltatime + 1;
            obj->m_transform = glm::rotate(obj->m_transform,glm::radians(rotation),  glm::vec3(0.0005f, 0.0000f, 0.0000f));
            i += 0.02;
        }

        m_renderer.Render(&m_scene);
        
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void Program::ProcessInput()
{
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(m_window, 1);
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
    glEnable(GL_DEPTH_TEST);
    void FramebufferSizeCallback(GLFWwindow * window, int width, int height);
    glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
}
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
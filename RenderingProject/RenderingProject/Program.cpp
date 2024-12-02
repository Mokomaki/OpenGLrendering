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
    auto t_start = std::chrono::high_resolution_clock::now();

    int lastScreenWidth = 800, lastScreenHeight = 600;
    int currentScreenWidth = 0, currentScreenHeight = 0;

    float timefromlastlog = 0;

    while (!glfwWindowShouldClose(m_window))
    {
        glfwGetWindowSize(m_window, &currentScreenWidth, &currentScreenHeight);
        if(currentScreenWidth != lastScreenWidth || currentScreenHeight != lastScreenHeight)
        {
            m_scene.m_camera->m_Projection = glm::perspective(glm::radians(80.0f), (float)currentScreenWidth / (float)currentScreenHeight, 0.1f, 100.0f);
            lastScreenWidth = currentScreenWidth;
            lastScreenHeight = currentScreenHeight;
        }
        //Timing
        auto t_now = std::chrono::high_resolution_clock::now();
        m_deltatime = std::chrono::duration_cast<std::chrono::duration<float>>(t_now - t_start).count();
        t_start = t_now;
        std::cout <<  1 / m_deltatime << std::endl;


        ProcessInput();

        for (auto obj : m_scene.GetWorldObjectsWithName("cube"))
        {
            float rotation = 20 * m_deltatime;
            obj->m_transform = glm::rotate(obj->m_transform,glm::radians(rotation),  glm::vec3(0.0000f, 1.0f, 0.0000f));
        }

        m_scene.m_uniformdata["cameraposition"]->SetUniformValue(m_scene.m_camera->Position);

        m_renderer.Render(&m_scene);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void Program::ProcessInput()
{

    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, 1);

    if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS)
    {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        m_scene.m_camera->ProcessKeyboard(CamConsts::CameraMovement::FORWARD,m_deltatime);
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        m_scene.m_camera->ProcessKeyboard(CamConsts::CameraMovement::BACKWARD, m_deltatime);
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        m_scene.m_camera->ProcessKeyboard(CamConsts::CameraMovement::LEFT, m_deltatime);
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        m_scene.m_camera->ProcessKeyboard(CamConsts::CameraMovement::RIGHT, m_deltatime);


    //MOUSE
    double xpos = 0;
    double ypos = 0;

    glfwGetCursorPos(m_window, &xpos, &ypos);

    if (m_firstMouseCallback)
    {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouseCallback = false;
    }

    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos;

    m_lastX = xpos;
    m_lastY = ypos;
    if (glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
        m_scene.m_camera->ProcessMouseMovement(xoffset, yoffset);
}


void Program::Initialize()
{
    //=====Initilize window=====
    
    //Init GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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
    void FramebufferSizeCallback(GLFWwindow * window, int width, int height);
    glfwSetFramebufferSizeCallback(m_window, FramebufferSizeCallback);
    glfwSwapInterval(0);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    m_isCursorEnabled = false;
    m_firstMouseCallback = true;
    m_lastX = 800 / 2.0f;
    m_lastY = 600 / 2.0f;

    //=====Initilize OpenGl=====

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}
void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
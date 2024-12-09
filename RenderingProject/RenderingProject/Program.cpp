#pragma once
#include "Program.h"


void Program::Run() 
{
    Initialize();
    m_scene.Initialize();
    
    //m_renderer->Render(&m_scene);
    RunApplicationLoop();
}

void Program::RunApplicationLoop()
{
    while (!glfwWindowShouldClose(m_window))
    {
        UpdateCameraOnResize();
        CalculateTiming(false);
        ProcessInput();

        for (auto obj : m_scene.GetWorldObjectsWithName("cube"))
        {
            float rotation = 20 * m_deltatime;
            obj->m_transform = glm::rotate(obj->m_transform,glm::radians(rotation),  glm::vec3(0.0000f, 1.0f, 0.0000f));
        }

        m_renderer->Render(&m_scene);
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

void Program::UpdateCameraOnResize()
{
    int currentScreenWidth = 0, currentScreenHeight = 0;
    glfwGetWindowSize(m_window, &currentScreenWidth, &currentScreenHeight);
    if (currentScreenWidth != m_screenWidth || currentScreenHeight != m_screenWidth)
    {
        m_scene.m_camera->m_Projection = glm::perspective(glm::radians(80.0f), (float)currentScreenWidth / (float)currentScreenHeight, 0.1f, 100.0f);
        m_screenWidth = currentScreenWidth;
        m_screenHeight = currentScreenHeight;
        m_renderer->SetViewportSize(m_screenWidth, m_screenHeight);
    }
}

void Program::CalculateTiming(bool printFPS)
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    m_deltatime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - m_lastFrameTime).count();
    m_lastFrameTime = currentTime;
    if (printFPS)
    {
        std::cout << "[FRAMETIME:] " << m_deltatime << std::endl;
        std::cout << "[FPS:] " << 1 / m_deltatime << std::endl;
    }
}

void Program::Initialize()
{
    m_applicationStartTime = std::chrono::high_resolution_clock::now();
    m_lastFrameTime = std::chrono::high_resolution_clock::now();
    m_screenWidth = 800;
    m_screenHeight = 600;

    //=====Initilize window=====
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);
    m_window = glfwCreateWindow(m_screenWidth, m_screenHeight, "Zerypth 2.0", NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    else
    {
        glfwMakeContextCurrent(m_window);
    }

    glfwSwapInterval(0);

    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    m_isCursorEnabled = false;
    m_firstMouseCallback = true;
    m_lastX = m_screenWidth / 2.0f;
    m_lastY = m_screenHeight / 2.0f;

    //=====Initilize OpenGl=====
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    m_renderer = new Renderer();
    m_renderer->SetViewportSize(m_screenWidth, m_screenHeight);
}
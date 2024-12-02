#pragma once
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <chrono>

#include "Renderer.h"
#include "Scene.h"
class Program {

public:
	void Run();
private:
	void Initialize();
	void RunApplicationLoop();
	void ProcessInput();
	void UpdateCameraOnResize();
	void CalculateTiming(bool printFPS);
private:
	GLFWwindow* m_window;
	Renderer m_renderer;
	Scene m_scene;
	std::chrono::steady_clock::time_point m_lastFrameTime;
	std::chrono::steady_clock::time_point m_applicationStartTime;
	bool m_firstMouseCallback;
	bool m_isCursorEnabled;
	float m_lastX;
	float m_lastY;
	float m_deltatime;
	int m_screenWidth;
	int m_screenHeight;
};
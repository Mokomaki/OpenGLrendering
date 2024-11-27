#pragma once
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <chrono>

#include "MeshRenderer.h"
#include "Scene.h"

class Program {

public:
	void Run();
private:
	void Initialize();
	void RunApplicationLoop();
	void ProcessInput();

private:
	GLFWwindow* m_window;
	MeshRenderer m_renderer;
	Scene m_scene;
	float m_deltatime;
};
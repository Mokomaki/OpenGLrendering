#pragma once
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>

#include "Shader.h"
#include "Mesh.h"
#include "MeshRenderer.h"

class Program {

public:
	void Run();

private:
	void Render();
	void Initialize();
	void RunApplicationLoop();
	void ProcessInput();
private:
	GLFWwindow* m_window;
	std::vector<MeshRenderer> m_renderers;
};
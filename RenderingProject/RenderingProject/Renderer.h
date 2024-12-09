#pragma once
#include <glad.h>
#include <glfw3.h>
#include <iostream>
#include <vector>
#include <set>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Scene.h"


class Renderer
{
public:
	Renderer();
	void Render(Scene* scene);
	void SetViewportSize(int width, int height);
private:
	void OpaquePass();
	void ShadowPass();
	void DrawElements(unsigned int indexCount);
	void ApplyUniforms(WorldObject& object, Scene& scene ,Shader& shader);
	void Clear(GLenum flags);
	void InitShadowFramebuffer();
private:
	Scene* m_currentScene;
	glm::vec4 m_clearColor;

	int m_screenWidth;
	int m_screenHeight;


	unsigned int quadVAO, quadVBO;
	Shader* m_debugshader;
	Shader* m_shadowObjectShader;
	glm::mat4 m_currentLightSpaceMatrix;
	unsigned int m_shadowFBO;
	unsigned int m_shadowFBwidth;
	unsigned int m_shadowFBheight;
	unsigned int m_shadowDepthMapID;
};
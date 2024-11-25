#include "Scene.h"

void Scene::Initialize()
{
    MeshRenderer myRenderer;
    Shader myShader;
    Mesh myMesh;
    Texture myTexture;

    myTexture.Initialize("D:/Pictures/MOONBABOON.png", GL_CLAMP_TO_BORDER);
    myMesh.CreatePrimitive(PrimitiveMeshShapes::TRIANGLE_MESH);
    myShader.GenerateShader("C:/Users/grest/source/repos/RenderingProgram/RenderingProject/RenderingProject/Image.shader");

    myRenderer.Initialize(&myMesh, &myShader);
    myRenderer.SetTexture(&myTexture);

    glm::mat4 transform = glm::mat4(1.0f);
    transform = glm::rotate(transform, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
    myRenderer.SetTransformation(transform);

    m_renderers.push_back(myRenderer);
}
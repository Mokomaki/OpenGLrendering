#pragma once
#include <vector>
#include <iostream>
#include <glad.h>
#include <glfw3.h>
#include <fstream>
#include <sstream>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Asset.h"


struct Vertex {
	float x, y, z;
	float u, v;
};

enum class PrimitiveMeshShapes
{
	TRIANGLE_MESH,
	PLANE_MESH,
	CUBE_MESH,
	SPHERE_MESH
};

class Mesh : public Asset
{
public:
	Mesh(PrimitiveMeshShapes shape);
	Mesh(const char* path, bool hasNormals);
	void Bind() override;
	ASSETTYPE GetAssetType() override;
	unsigned int GetIndexCount();

private:
	unsigned int GetVertexCount();
	unsigned int* GetIndices();
	Vertex* GetVertices();
	void InitBuffers();
	void CreatePrimitive(PrimitiveMeshShapes shape);
	void CreateFromFile(const char* path, bool hasNormals);
	glm::vec3 Parse3Floats(std::string& text);
	glm::vec2 Parse2Floats(std::string& text);
	void Parse6Ints(std::string& text, unsigned int* vertexArray, unsigned int* uvArray);
	void Parse9Ints(std::string& text, unsigned int* vertexArray, unsigned int* uvArray, unsigned int* normalArray);

	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	unsigned int m_indexCount;
	unsigned int m_vertexCount;
	unsigned int m_vao, m_vbo, m_ebo;
};
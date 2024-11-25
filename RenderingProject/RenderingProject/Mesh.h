#pragma once
#include <vector>
#include <iostream>

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

class Mesh
{
public:
	void CreatePrimitive(PrimitiveMeshShapes shape);
	void CreateFromData(Vertex* vertices,unsigned int* indices);
	Vertex* GetVertices();
	unsigned int* GetIndices();
	unsigned int GetVertexCount();
	unsigned int GetIndexCount();

private:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned int> m_indices;
	unsigned int m_indexCount;
	unsigned int m_vertexCount;
};
#include "Mesh.h"

void Mesh::CreatePrimitive(PrimitiveMeshShapes shape)
{
	switch (shape)
	{
	case PrimitiveMeshShapes::TRIANGLE_MESH:
		//						 x		y	  z      u      v
		m_vertices.push_back({ -0.5f, -0.5f, 0.0f,  0.0f,  0.0 });
		m_vertices.push_back({  0.5f, -0.5f, 0.0f,  1.0f,  0.0 });
		m_vertices.push_back({  0.0f,  0.5f, 0.0f,  0.5f,  1.0 });
		m_vertexCount = 3;

		m_indices.push_back(0);
		m_indices.push_back(1);
		m_indices.push_back(2);
		m_indexCount = 3;
		break;
	case PrimitiveMeshShapes::PLANE_MESH:
		m_vertices.push_back({ 0.5f,  0.5f, 0.0f,  1.0f, 1.0f });
		m_vertices.push_back({ 0.5f, -0.5f, 0.0f,  1.0f, 0.0f });
		m_vertices.push_back({-0.5f, -0.5f, 0.0f,  0.0f, 0.0f });
		m_vertices.push_back({-0.5f,  0.5f, 0.0f,  0.0f, 1.0f });
		m_vertexCount = 4;

		m_indices.push_back(0);
		m_indices.push_back(1);
		m_indices.push_back(3);
		m_indices.push_back(1);
		m_indices.push_back(2);
		m_indices.push_back(3);
		m_indexCount = 6;
		break;
	case PrimitiveMeshShapes::CUBE_MESH:
		std::cout << "Primitive 'CUBE' not implemented!" << std::endl;
		break;
	case PrimitiveMeshShapes::SPHERE_MESH:
		std::cout << "Primitive 'SPHERE' not implemented!" << std::endl;
		break;
	default:
		break;
	}
}

Vertex* Mesh::GetVertices()
{
	return m_vertices.data();
}

unsigned int* Mesh::GetIndices()
{
	return m_indices.data();
}

unsigned int Mesh::GetVertexCount()
{
	return m_vertexCount;
}
unsigned int Mesh::GetIndexCount()
{
	return m_indexCount;
}
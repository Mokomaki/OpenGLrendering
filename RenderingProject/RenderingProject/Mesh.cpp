#pragma once
#include "Mesh.h"
#include <glad.h>
#include <glfw3.h>

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

void Mesh::InitBuffers()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	glBindVertexArray(m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * GetVertexCount(), GetVertices(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * GetIndexCount(), GetIndices(), GL_STATIC_DRAW);

	//Vertex layout
	//CURRENT VERTEX STRIDE: 5 * FLOAT
	//Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(0);
	//UV attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

void Mesh::Bind()
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
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
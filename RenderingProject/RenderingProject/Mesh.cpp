#pragma once
#include "Mesh.h"


void Mesh::CreatePrimitive(PrimitiveMeshShapes shape)
{
	switch (shape)
	{
	case PrimitiveMeshShapes::TRIANGLE_MESH:
		//						 x		y	  z      u      v
		m_vertices.push_back({ -1.0f, -1.0f, 0.0f,  0.0f,  0.0 });
		m_vertices.push_back({  1.0f, -1.0f, 0.0f,  1.0f,  0.0 });
		m_vertices.push_back({  0.0f,  1.0f, 0.0f,  0.5f,  1.0 });
		m_vertexCount = 3;

		m_indices.push_back(0);
		m_indices.push_back(1);
		m_indices.push_back(2);
		m_indexCount = 3;
		break;
	case PrimitiveMeshShapes::PLANE_MESH:
		m_vertices.push_back({ 1.0f,  1.0f, 0.0f,  1.0f, 1.0f });
		m_vertices.push_back({ 1.0f, -1.0f, 0.0f,  1.0f, 0.0f });
		m_vertices.push_back({-1.0f, -1.0f, 0.0f,  0.0f, 0.0f });
		m_vertices.push_back({-1.0f,  1.0f, 0.0f,  0.0f, 1.0f });
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
		m_vertices.push_back({  1.0f,  1.0f, -1.0f,  1.0f, 1.0f });
		m_vertices.push_back({  1.0f, -1.0f, -1.0f,  1.0f, 0.0f });
		m_vertices.push_back({ -1.0f, -1.0f, -1.0f,  0.0f, 0.0f });
		m_vertices.push_back({ -1.0f,  1.0f, -1.0f,  0.0f, 1.0f });

		m_vertices.push_back({ -1.0f, -1.0f,  1.0f,  1.0f, 1.0f });
		m_vertices.push_back({ -1.0f,  1.0f,  1.0f,  1.0f, 0.0f });
		m_vertices.push_back({  1.0f,  1.0f,  1.0f,  0.0f, 0.0f });
		m_vertices.push_back({  1.0f, -1.0f,  1.0f,  0.0f, 1.0f });

		m_vertices.push_back({ 1.0f,  1.0f,   1.0f,  1.0f, 1.0f });
		m_vertices.push_back({ 1.0f, -1.0f,   1.0f,  1.0f, 0.0f });
		m_vertices.push_back({ 1.0f, -1.0f,  -1.0f,  0.0f, 0.0f });
		m_vertices.push_back({ 1.0f,  1.0f,  -1.0f,  0.0f, 1.0f });

		m_vertices.push_back({ -1.0f, -1.0f, -1.0f,  1.0f, 1.0f });
		m_vertices.push_back({ -1.0f,  1.0f, -1.0f,  1.0f, 0.0f });
		m_vertices.push_back({ -1.0f,  1.0f,  1.0f,  0.0f, 0.0f });
		m_vertices.push_back({ -1.0f, -1.0f,  1.0f,  0.0f, 1.0f });

		m_vertices.push_back({  1.0f,  1.0f ,  1.0f,  1.0f, 1.0f });
		m_vertices.push_back({ -1.0f,  1.0f ,  1.0f,  1.0f, 0.0f });
		m_vertices.push_back({ -1.0f,  1.0f , -1.0f,  0.0f, 0.0f });
		m_vertices.push_back({  1.0f,  1.0f , -1.0f,  0.0f, 1.0f });

		m_vertices.push_back({ -1.0f, 1.0f,  0.5f,  1.0f, 1.0f });
		m_vertices.push_back({  1.0f, -1.0f,  0.5f,  1.0f, 0.0f });
		m_vertices.push_back({  1.0f, -1.0f,  0.5f,  0.0f, 0.0f });
		m_vertices.push_back({ -1.0f, 1.0f,  0.5f,  0.0f, 1.0f });

		m_vertexCount = 16;

		m_indices.push_back(0);
		m_indices.push_back(1);
		m_indices.push_back(3);
		m_indices.push_back(1);
		m_indices.push_back(2);
		m_indices.push_back(3);

		m_indices.push_back(4);
		m_indices.push_back(5);
		m_indices.push_back(7);
		m_indices.push_back(5);
		m_indices.push_back(6);
		m_indices.push_back(7);

		m_indices.push_back(8);
		m_indices.push_back(9);
		m_indices.push_back(11);
		m_indices.push_back(9);
		m_indices.push_back(10);
		m_indices.push_back(11);

		m_indices.push_back(12);
		m_indices.push_back(13);
		m_indices.push_back(15);
		m_indices.push_back(13);
		m_indices.push_back(14);
		m_indices.push_back(15);

		m_indices.push_back(16);
		m_indices.push_back(17);
		m_indices.push_back(19);
		m_indices.push_back(17);
		m_indices.push_back(18);
		m_indices.push_back(19);

		m_indices.push_back(20);
		m_indices.push_back(21);
		m_indices.push_back(23);
		m_indices.push_back(21);
		m_indices.push_back(22);
		m_indices.push_back(23);

		m_indexCount = 36;
		break;
	case PrimitiveMeshShapes::SPHERE_MESH:
		std::cout << "Primitive 'SPHERE' not implemented!" << std::endl;
		break;
	default:
		break;
	}

}

void Mesh::CreateFromFile(const char* path, bool hasNormals)
{

	//READING AND PARSING FILE
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	std::ifstream stream(path);
	std::string line;
	while (std::getline(stream, line))
	{
		if(line.substr(0, line.find(" "))=="v"){
			temp_vertices.push_back(Parse3Floats(line));
		}else if (line.substr(0, line.find(" ")) == "vt"){
			temp_uvs.push_back(Parse2Floats(line));
		}else if (line.substr(0, line.find(" ")) == "vn"){
			temp_normals.push_back(Parse3Floats(line));
		}else if (line.substr(0, line.find(" ")) == "f")
		{
			if (hasNormals)
			{
				std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = scanf_s(line.c_str(), "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9)
				{
					std::cout << "ERROR: Cannot parse mesh from file!" << std::endl;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
			else
			{
				unsigned int vertexIndex[3], uvIndex[3];
				Parse6Ints(line, vertexIndex, uvIndex);
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
			}
		}


	}
	//CREATING VERTICES
	for (int i = 0; i < vertexIndices.size();i++)
	{
		Vertex vert = {
			temp_vertices[vertexIndices[i] - 1].x,
			temp_vertices[vertexIndices[i] - 1].y,
			temp_vertices[vertexIndices[i] - 1].z,
			temp_uvs[uvIndices[i] - 1].x,
			temp_uvs[uvIndices[i] - 1].y
		    //temp_normals[normalIndices[i] - 1].x,
			//temp_normals[normalIndices[i] - 1].y,		ENABLE WHEN IMPLEMENTING NORMALS
			//temp_normals[normalIndices[i] - 1].z,
		};
		m_vertices.push_back(vert);
		m_vertexCount = m_vertices.size();
	}
	for (int i = 0; i < vertexIndices.size(); i += 3)
	{
		m_indices.push_back(i);
		m_indices.push_back(i + 1);
		m_indices.push_back(i + 2);
		m_indexCount = m_indices.size();
	}

}

glm::vec3 Mesh::Parse3Floats(std::string& text)
{
	//Erase the beginning of the line
	text.erase(0, text.find(" ")+1);
	std::string first = text.substr(0, text.find(" "));
	text.erase(0, text.find(" ")+1);
	std::string second = text.substr(0, text.find(" "));
	text.erase(0, text.find(" ")+1);
	std::string third = text.substr(0, text.length());
	glm::vec3 out = glm::vec3(std::stof(first), std::stof(second), std::stof(third));
	return out;
}
glm::vec2 Mesh::Parse2Floats(std::string& text)
{
	//Erase the beginning of the line
	text.erase(0, text.find(" ")+1);
	std::string first = text.substr(0, text.find(" "));
	text.erase(0, text.find(" ")+1);
	std::string second = text.substr(0, text.length());
	glm::vec2 out = glm::vec2(std::stof(first), std::stof(second));
	return out;
}
void Mesh::Parse6Ints(std::string& text, unsigned int* vertexArray, unsigned int* uvArray)
{
	//Erase the beginning of the line
	text.erase(0, text.find(" ")+1);
	std::string first = text.substr(0, text.find(" "));
	text.erase(0, text.find(" ")+1);
	std::string second = text.substr(0, text.find(" "));
	text.erase(0, text.find(" ")+1);
	std::string third = text.substr(0, text.length());
	//vertexArray[0]
	vertexArray[0] = (unsigned int)std::stoul(first.substr(0, first.find("/")));
	first.erase(0, first.find("/")+1);
	uvArray[0] = (unsigned int)std::stoul(first.substr(0, first.find(" ")));
	
	vertexArray[1] = (unsigned int)std::stoul(second.substr(0, second.find("/")));
	second.erase(0, second.find("/")+1);
	uvArray[1] = (unsigned int)std::stoul(second.substr(0, second.find(" ")));

	vertexArray[2] = (unsigned int)std::stoul(third.substr(0, third.find("/")));
	third.erase(0, third.find("/")+1);
	uvArray[2] = (unsigned int)std::stoul(third.substr(0, third.length()));

}
void Mesh::Parse9Ints(std::string& text, unsigned int* vertexArray, unsigned int* uvArray, unsigned int* normalArray)
{
	std::cout << "ERROR: Normals not implemented!" << std::endl;
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
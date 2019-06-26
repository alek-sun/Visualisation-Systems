#include "MeshSphere.h"
#include "GraphicsEngine/MathConstants.h"
#include <stdlib.h>


void GetVertexOnSphere(int i, int iMax, int j, int jMax, Vector3 & v, Vector3 & n, Vector4 & c, Vector3 & uv0)
{
	const double radius = 0.5f;

	double theta	= (180.0 - 180.0 * j / (jMax - 1)) * DEG2RAD;
	double phi		= (360.0 * (i % iMax) / iMax) * DEG2RAD;

	v.x		= radius * sin(theta) * cos(phi);
	v.y		= radius * cos(theta);
	v.z		= radius * sin(theta) * sin(phi);

	Vector3 normal(v.x, v.y, v.z);
	normal.Normalize();
	n.x	= normal.x;
	n.y	= normal.y;
	n.z	= normal.z;

	double r = (rand() % 255) / 255.0f;
	double g = (rand() % 255) / 255.0f;
	double b = (rand() % 255) / 255.0f;
	double a = 1.0f;
	c = Vector4(r, g, b, 1);

	uv0.x = 1.0f * i / iMax;
	uv0.y = 1.0f * (jMax - 1 - j) / (jMax - 1);
}


MeshSphere::MeshSphere(int levelCount)
{
	m_levelCount = (levelCount < 3) ? 3 : levelCount;
}

void MeshSphere::Init()
{
	Mesh::Init();

	std::vector<Vector3> vertices;
	std::vector<Vector4> colors;
	std::vector<Vector3> normals;
	std::vector<Vector3> uv0;
	std::vector<int> indices;
	
	int vertexInRowCount = m_levelCount + 1 + 2;
	int vertexCount = vertexInRowCount * m_levelCount;
    
	vertices.resize(vertexCount);
	normals.resize(vertexCount);
	colors.resize(vertexCount);
	uv0.resize(vertexCount);

	for (int j = 0; j < m_levelCount; ++j)
	{
		for (int i = 0; i < m_levelCount + 1; ++i)
		{
			int k = vertexInRowCount * j + i;
			GetVertexOnSphere(i, m_levelCount, j, m_levelCount, vertices[k], normals[k], colors[k], uv0[k]);
		}

		// Добавляем вершины для вырожденных треугольников
		int k1 = vertexInRowCount * j + (m_levelCount + 1 + 0);
		int k2 = vertexInRowCount * j + (m_levelCount + 0);
		vertices[k1]	= vertices[k2];
		normals[k1]		= normals[k2];
		
		// Последний раз добавлять не нужно
		if (j < m_levelCount - 1)
		{			
			int k = vertexInRowCount * j + (m_levelCount + 1 + 1);
			GetVertexOnSphere(0, m_levelCount, j + 1, m_levelCount, vertices[k], normals[k], colors[k], uv0[k]);
		}
		else
		{
			int k1 = vertexInRowCount * j + (m_levelCount + 1 + 1);
			int k2 = vertexInRowCount * j + (m_levelCount + 0);
			vertices[k1]	= vertices[k2];
			normals[k1]		= normals[k2];
		}
	}

	int indexCount = (m_levelCount - 1) * vertexInRowCount * 2;
	indices.resize(indexCount);
	for (int j = 0; j < (m_levelCount - 1); ++j)
	{
		for (int i = 0; i < vertexInRowCount; ++i)
		{
			indices[j * vertexInRowCount * 2 + i * 2 + 0] = j * vertexInRowCount + i;
			indices[j * vertexInRowCount * 2 + i * 2 + 1] = j * vertexInRowCount + vertexInRowCount + i;
		}
	}

	
	meshImpl->SetVertices(vertices);
	meshImpl->SetColors(colors);
	meshImpl->SetNormals(normals);
	meshImpl->SetUV0(uv0);

	meshImpl->SetIndices(indices, MESH_TOPOLOGY_TRIANGLE_STRIP);
	
	meshImpl->Apply();
}

void MeshSphere::Deinit()
{
	Mesh::Deinit();
}

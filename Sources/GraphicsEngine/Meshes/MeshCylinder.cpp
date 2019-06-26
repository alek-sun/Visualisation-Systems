#include "MeshCylinder.h"
#include "GraphicsEngine/MathConstants.h"
#include <stdlib.h>


void GetVertexOnCylinder(double radius, int i, int iMax, int j, int jMax, Vector3 & v, Vector3 & n, Vector4 & c, Vector3 & uv0)
{
	//const double radius = 0.5f;
	const double height = 2.0f;

	double phi		= (360.0 * (i % iMax) / iMax) * DEG2RAD;

	v.x		= radius * cos(phi);
	v.y		= height * (1.0f * j / (jMax - 1) - 0.5f);
	v.z		= radius * sin(phi);

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
	uv0.y = 1.0f * j / (jMax - 1);
}


MeshCylinder::MeshCylinder(int levelCount)
{
	m_levelCount = (levelCount < 3) ? 3 : levelCount;
}

void MeshCylinder::Init()
{
	Mesh::Init();

	std::vector<Vector3> vertices;
	std::vector<Vector4> colors;
	std::vector<Vector3> normals;
	std::vector<Vector3> uv0;
	
	std::vector<int> indices;
	
	int vertexInRowCount = m_levelCount + 1 + 2;
	int vertexCount = vertexInRowCount * (m_levelCount + 1);
    
	vertices.resize(vertexCount);
	colors.resize(vertexCount);
	normals.resize(vertexCount);
	uv0.resize(vertexCount);

	const double radius = 0.5f;

	// Side
	for (int j = 0; j < m_levelCount; ++j)
	{
		for (int i = 0; i < m_levelCount + 1; ++i)
		{
			int k = vertexInRowCount * j + i;
			GetVertexOnCylinder(radius, i, m_levelCount, j, m_levelCount, vertices[k], normals[k], colors[k], uv0[k]);
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
			GetVertexOnCylinder(radius, 0, m_levelCount, j + 1, m_levelCount, vertices[k], normals[k], colors[k], uv0[k]);
		}
		else
		{
			int k1 = vertexInRowCount * j + (m_levelCount + 1 + 1);
			int k2 = vertexInRowCount * j + (m_levelCount + 1);
			vertices[k1]	= vertices[k2];
			normals[k1]		= normals[k2];
		}
	}

	int idxTop = 0;
	// Top circle
	{
		int k = vertexInRowCount * m_levelCount + 0;
		GetVertexOnCylinder(0, 0, m_levelCount, m_levelCount - 1, m_levelCount, vertices[k], normals[k], colors[k], uv0[k]);

		idxTop = k;
	}

	// Bottom circle
	int idxBottom = 0;
	{
		int k = vertexInRowCount * m_levelCount + 1;
		GetVertexOnCylinder(0, 0, m_levelCount, 0, m_levelCount, vertices[k], normals[k], colors[k], uv0[k]);

		idxBottom = k;
	}

	int indexCount = (m_levelCount - 1 + 2) * vertexInRowCount * 2;
	indices.resize(indexCount);

	// Side
	for (int j = 0; j < (m_levelCount - 1); ++j)
	{
		for (int i = 0; i < vertexInRowCount; ++i)
		{
			indices[j * vertexInRowCount * 2 + i * 2 + 0] = j * vertexInRowCount + i;
			indices[j * vertexInRowCount * 2 + i * 2 + 1] = j * vertexInRowCount + vertexInRowCount + i;
		}
	}

	// Top circle
	{
		for (int i = 0; i < m_levelCount + 1; ++i)
		{
			int j = m_levelCount - 1;
			indices[j * vertexInRowCount * 2 + i * 2 + 0] = j * vertexInRowCount + i;
			indices[j * vertexInRowCount * 2 + i * 2 + 1] = idxTop;
		}

		{
			int j = m_levelCount - 1;
			int i = m_levelCount + 1;
			indices[j * vertexInRowCount * 2 + i * 2 + 0] = indices[j * vertexInRowCount * 2 + (i - 1) * 2 + 1];
			indices[j * vertexInRowCount * 2 + i * 2 + 1] = indices[j * vertexInRowCount * 2 + (i - 1) * 2 + 1];
			indices[j * vertexInRowCount * 2 + i * 2 + 2] = idxBottom;
			indices[j * vertexInRowCount * 2 + i * 2 + 3] = idxBottom;
		}
	}

	// Bottom circle
	{
		for (int i = 0; i < m_levelCount + 1; ++i)
		{
			int j = m_levelCount;
			indices[j * vertexInRowCount * 2 + i * 2 + 0] = idxBottom;
			indices[j * vertexInRowCount * 2 + i * 2 + 1] = 0 * vertexInRowCount + i;
		}

		{
			int j = m_levelCount;
			int i = m_levelCount + 1;
			indices[j * vertexInRowCount * 2 + i * 2 + 0] = indices[j * vertexInRowCount * 2 + (i - 1) * 2 + 1];
			indices[j * vertexInRowCount * 2 + i * 2 + 1] = indices[j * vertexInRowCount * 2 + (i - 1) * 2 + 1];
			indices[j * vertexInRowCount * 2 + i * 2 + 2] = indices[j * vertexInRowCount * 2 + (i - 1) * 2 + 1];
			indices[j * vertexInRowCount * 2 + i * 2 + 3] = indices[j * vertexInRowCount * 2 + (i - 1) * 2 + 1];
		}
	}

	
	meshImpl->SetVertices(vertices);
	meshImpl->SetColors(colors);
	meshImpl->SetNormals(normals);
	meshImpl->SetUV0(uv0);
	
	meshImpl->SetIndices(indices, MESH_TOPOLOGY_TRIANGLE_STRIP);

	meshImpl->Apply();
}

void MeshCylinder::Deinit()
{
	Mesh::Deinit();
}

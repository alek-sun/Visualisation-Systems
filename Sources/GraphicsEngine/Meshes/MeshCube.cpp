#include "MeshCube.h"
#include <stdlib.h>


MeshCube::MeshCube(int levelCount)
{
	m_levelCount = (levelCount < 1) ? 1 : levelCount;
}

void MeshCube::Init()
{
	Mesh::Init();

	if (1 == m_levelCount)
	{
		InitCubeSimple();
	}
	else
	{
		//InitCubeDetailedStrip();
		InitCubeDetailedList();
	}
}

void MeshCube::Deinit()
{
	Mesh::Deinit();
}

void MeshCube::InitCubeSimple()
{
	std::vector<Vector3> vertices;
	{
		vertices.push_back( Vector3(-0.5f,-0.5f,-0.5f) ); // 0	
		vertices.push_back( Vector3(-0.5f, 0.5f,-0.5f) ); // 1
		vertices.push_back( Vector3( 0.5f,-0.5f,-0.5f) ); // 2
		vertices.push_back( Vector3( 0.5f, 0.5f,-0.5f) ); // 3

		vertices.push_back( Vector3( 0.5f,-0.5f,-0.5f) ); // 4
		vertices.push_back( Vector3( 0.5f, 0.5f,-0.5f) ); // 5	
		vertices.push_back( Vector3( 0.5f,-0.5f, 0.5f) ); // 6
		vertices.push_back( Vector3( 0.5f, 0.5f, 0.5f) ); // 7

		vertices.push_back( Vector3( 0.5f,-0.5f, 0.5f) ); // 8
		vertices.push_back( Vector3( 0.5f, 0.5f, 0.5f) ); // 9
		vertices.push_back( Vector3(-0.5f,-0.5f, 0.5f) ); // 10
		vertices.push_back( Vector3(-0.5f, 0.5f, 0.5f) ); // 11

		vertices.push_back( Vector3(-0.5f,-0.5f, 0.5f) ); // 12
		vertices.push_back( Vector3(-0.5f, 0.5f, 0.5f) ); // 13
		vertices.push_back( Vector3(-0.5f,-0.5f,-0.5f) ); // 13
		vertices.push_back( Vector3(-0.5f, 0.5f,-0.5f) ); // 15

		vertices.push_back( Vector3(-0.5f, 0.5f,-0.5f) ); // 16
		vertices.push_back( Vector3(-0.5f, 0.5f, 0.5f) ); // 17
		vertices.push_back( Vector3( 0.5f, 0.5f,-0.5f) ); // 18
		vertices.push_back( Vector3( 0.5f, 0.5f, 0.5f) ); // 19

		vertices.push_back( Vector3( 0.5f, 0.5f, 0.5f) ); // 20
		vertices.push_back( Vector3( 0.5f,-0.5f, 0.5f) ); // 21
		
		vertices.push_back( Vector3( 0.5f,-0.5f, 0.5f) ); // 22
		vertices.push_back( Vector3(-0.5f,-0.5f, 0.5f) ); // 23
		vertices.push_back( Vector3( 0.5f,-0.5f,-0.5f) ); // 24
		vertices.push_back( Vector3(-0.5f,-0.5f,-0.5f) ); // 25
	}

	std::vector<Vector4> colors;
	{
		colors.push_back( Vector4(1.0f, 0.0f, 0.0f, 1.0f) ); // 0	
		colors.push_back( Vector4(1.0f, 0.0f, 0.0f, 1.0f) ); // 1
		colors.push_back( Vector4(1.0f, 0.0f, 0.0f, 1.0f) ); // 2
		colors.push_back( Vector4(1.0f, 0.0f, 0.0f, 1.0f) ); // 3

		colors.push_back( Vector4(0.0f, 1.0f, 0.0f, 1.0f) ); // 4
		colors.push_back( Vector4(0.0f, 1.0f, 0.0f, 1.0f) ); // 5	
		colors.push_back( Vector4(0.0f, 1.0f, 0.0f, 1.0f) ); // 6
		colors.push_back( Vector4(0.0f, 1.0f, 0.0f, 1.0f) ); // 7

		colors.push_back( Vector4(0.0f, 0.0f, 1.0f, 1.0f) ); // 8
		colors.push_back( Vector4(0.0f, 0.0f, 1.0f, 1.0f) ); // 9
		colors.push_back( Vector4(0.0f, 0.0f, 1.0f, 1.0f) ); // 10
		colors.push_back( Vector4(0.0f, 0.0f, 1.0f, 1.0f) ); // 11

		colors.push_back( Vector4(1.0f, 1.0f, 0.0f, 1.0f) ); // 12
		colors.push_back( Vector4(1.0f, 1.0f, 0.0f, 1.0f) ); // 13
		colors.push_back( Vector4(1.0f, 1.0f, 0.0f, 1.0f) ); // 13
		colors.push_back( Vector4(1.0f, 1.0f, 0.0f, 1.0f) ); // 15

		colors.push_back( Vector4(0.0f, 1.0f, 1.0f, 1.0f) ); // 16
		colors.push_back( Vector4(0.0f, 1.0f, 1.0f, 1.0f) ); // 17
		colors.push_back( Vector4(0.0f, 1.0f, 1.0f, 1.0f) ); // 18
		colors.push_back( Vector4(0.0f, 1.0f, 1.0f, 1.0f) ); // 19

		colors.push_back( Vector4(0.0f, 1.0f, 1.0f, 1.0f) ); // 20
		colors.push_back( Vector4(1.0f, 0.0f, 1.0f, 1.0f) ); // 21
		
		colors.push_back( Vector4(1.0f, 0.0f, 1.0f, 1.0f) ); // 22
		colors.push_back( Vector4(1.0f, 0.0f, 1.0f, 1.0f) ); // 23
		colors.push_back( Vector4(1.0f, 0.0f, 1.0f, 1.0f) ); // 24
		colors.push_back( Vector4(1.0f, 0.0f, 1.0f, 1.0f) ); // 25
	}

	std::vector<Vector3> normals;
	{
		normals.push_back( Vector3( 0.0f, 0.0f, -1.0f) ); // 0	
		normals.push_back( Vector3( 0.0f, 0.0f, -1.0f) ); // 1
		normals.push_back( Vector3( 0.0f, 0.0f, -1.0f) ); // 2
		normals.push_back( Vector3( 0.0f, 0.0f, -1.0f) ); // 3

		normals.push_back( Vector3( 1.0f, 0.0f,  0.0f) ); // 4
		normals.push_back( Vector3( 1.0f, 0.0f,  0.0f) ); // 5	
		normals.push_back( Vector3( 1.0f, 0.0f,  0.0f) ); // 6
		normals.push_back( Vector3( 1.0f, 0.0f,  0.0f) ); // 7

		normals.push_back( Vector3( 0.0f, 0.0f,  1.0f) ); // 8
		normals.push_back( Vector3( 0.0f, 0.0f,  1.0f) ); // 9
		normals.push_back( Vector3( 0.0f, 0.0f,  1.0f) ); // 10
		normals.push_back( Vector3( 0.0f, 0.0f,  1.0f) ); // 11

		normals.push_back( Vector3(-1.0f, 0.0f,  0.0f) ); // 12
		normals.push_back( Vector3(-1.0f, 0.0f,  0.0f) ); // 13
		normals.push_back( Vector3(-1.0f, 0.0f,  0.0f) ); // 13
		normals.push_back( Vector3(-1.0f, 0.0f,  0.0f) ); // 15

		normals.push_back( Vector3( 0.0f, 1.0f,  0.0f) ); // 16
		normals.push_back( Vector3( 0.0f, 1.0f,  0.0f) ); // 17
		normals.push_back( Vector3( 0.0f, 1.0f,  0.0f) ); // 18
		normals.push_back( Vector3( 0.0f, 1.0f,  0.0f) ); // 19

		normals.push_back( Vector3( 0.0f, 1.0f,  0.0f) ); // 20
		normals.push_back( Vector3( 0.0f,-1.0f,  0.0f) ); // 21
		
		normals.push_back( Vector3( 0.0f,-1.0f,  0.0f) ); // 22
		normals.push_back( Vector3( 0.0f,-1.0f,  0.0f) ); // 23
		normals.push_back( Vector3( 0.0f,-1.0f,  0.0f) ); // 24
		normals.push_back( Vector3( 0.0f,-1.0f,  0.0f) ); // 25
	}

	std::vector<Vector3> uv0;
	{
		Vector3 uv00(0, 0, 0);
		Vector3 uv10(1, 0, 0);
		Vector3 uv01(0, 1, 0);
		Vector3 uv11(1, 1, 0);

		uv0.push_back( uv00 ); // 0	
		uv0.push_back( uv01 ); // 1
		uv0.push_back( uv10 ); // 2
		uv0.push_back( uv11 ); // 3

		uv0.push_back( uv00 ); // 4
		uv0.push_back( uv01 ); // 5	
		uv0.push_back( uv10 ); // 6
		uv0.push_back( uv11 ); // 7

		uv0.push_back( uv00 ); // 8
		uv0.push_back( uv01 ); // 9
		uv0.push_back( uv10 ); // 10
		uv0.push_back( uv11 ); // 11

		uv0.push_back( uv00 ); // 12
		uv0.push_back( uv01 ); // 13
		uv0.push_back( uv10 ); // 13
		uv0.push_back( uv11 ); // 15

		uv0.push_back( uv00 ); // 16
		uv0.push_back( uv01 ); // 17
		uv0.push_back( uv10 ); // 18
		uv0.push_back( uv11 ); // 19

		uv0.push_back( uv11 ); // 20
		uv0.push_back( uv00 ); // 21
		
		uv0.push_back( uv00 ); // 22
		uv0.push_back( uv01 ); // 23
		uv0.push_back( uv10 ); // 24
		uv0.push_back( uv11 ); // 25
	}
	
	std::vector<int> indices;
	for (int i = 0; i <= 25; ++i)
	{
		indices.push_back(i);
	}

	
	meshImpl->SetVertices(vertices);
	meshImpl->SetColors(colors);
	meshImpl->SetNormals(normals);
	meshImpl->SetUV0(uv0);
	
	meshImpl->SetIndices(indices, MESH_TOPOLOGY_TRIANGLE_STRIP);

	meshImpl->Apply();
}

void SetVertexOnPlane(int idx, int i, int iMax, int j, int jMax, const Vector3 & bottomLeft, const Vector3 & right, const Vector3 & up,
						std::vector<Vector3> & v, std::vector<Vector3> & n, std::vector<Vector4> & c, const Vector4 & color)
{
	v[idx] = bottomLeft + right * (1.0f * i / iMax) + up * (1.0f * j / jMax);
	n[idx] = Vector3::Cross(right, up).Normalize() * (-1.0); // (-1.0) means left coordinate system
	c[idx] = color;
}

void FillPlane(const Vector3 & bottomLeft, const Vector3 & right, const Vector3 & up, int m_levelCount, 
			   int vertexInRowCount, int indexInRowCount, 
			   std::vector<Vector3> & vertices, std::vector<Vector3> & normals, std::vector<Vector4> & colors, std::vector<int> & indices,
			   int planeIndex)
{
	const int iMax = m_levelCount;
	const int jMax = m_levelCount;
	int vertexShift = planeIndex * vertexInRowCount * vertexInRowCount;

	for (int j = 0; j < jMax + 1; ++j)
	{
		for (int i = 0; i < iMax + 1; ++i)
		{
			int idx = vertexShift + vertexInRowCount * j + i;
			Vector4 color;
			{
				double r = (rand() % 255) / 255.0f;
				double g = (rand() % 255) / 255.0f;
				double b = (rand() % 255) / 255.0f;
				double a = 1.0f;
				color = Vector4(r, g, b, 1);
			}
			
			SetVertexOnPlane(idx, i, iMax, j, jMax, bottomLeft, right, up, vertices, normals, colors, color);
		}		
	}


	int indexShift = planeIndex * indexInRowCount * m_levelCount;

	if (planeIndex > 0)
	{
		indices[indexShift - 1] = vertexShift;
	}

	for (int j = 0; j < m_levelCount; ++j)
	{
		for (int i = 0; i < vertexInRowCount; ++i)
		{
			indices[indexShift + j * indexInRowCount + i * 2 + 0] = vertexShift + j * vertexInRowCount + i;
			indices[indexShift + j * indexInRowCount + i * 2 + 1] = vertexShift + j * vertexInRowCount + vertexInRowCount + i;
		}

		indices[indexShift + j * indexInRowCount + vertexInRowCount * 2 + 0] = indices[indexShift + j * indexInRowCount + vertexInRowCount * 2 - 1];
		indices[indexShift + j * indexInRowCount + vertexInRowCount * 2 + 1] = vertexShift + j * vertexInRowCount + vertexInRowCount;
	}
}

void MeshCube::InitCubeDetailedStrip()
{
	int vertexInRowCount	= m_levelCount + 1;
	int vertexInPlaneCount	= vertexInRowCount * vertexInRowCount;
	int vertexCount			= vertexInPlaneCount * 6;
	
	std::vector<Vector3> vertices;
	std::vector<Vector3> normals;
	std::vector<Vector4> colors;

	vertices.resize(vertexCount);
	normals.resize(vertexCount);
	colors.resize(vertexCount);

	
	int indexInRowCount		= (vertexInRowCount * 2 + 2);
	int indexInPlaneCount	= indexInRowCount * m_levelCount;
	int indexCount			= indexInPlaneCount * 6;

	std::vector<int> indices;
	
	indices.resize(indexCount);
	
	FillPlane(Vector3(-0.5f, -0.5f, -0.5f), Vector3( 1.0f, 0.0f, 0.0f), Vector3( 0.0f, 1.0f, 0.0f),
						  m_levelCount, vertexInRowCount, indexInRowCount, vertices, normals, colors, indices, 0);

	FillPlane(Vector3( 0.5f, -0.5f, -0.5f), Vector3( 0.0f, 0.0f, 1.0f), Vector3( 0.0f, 1.0f, 0.0f),
						  m_levelCount, vertexInRowCount, indexInRowCount, vertices, normals, colors, indices, 1);

	FillPlane(Vector3( 0.5f, -0.5f,  0.5f), Vector3(-1.0f, 0.0f, 0.0f), Vector3( 0.0f, 1.0f, 0.0f),
						  m_levelCount, vertexInRowCount, indexInRowCount, vertices, normals, colors, indices, 2);

	FillPlane(Vector3(-0.5f, -0.5f,  0.5f), Vector3( 0.0f, 0.0f,-1.0f), Vector3( 0.0f, 1.0f, 0.0f),
						  m_levelCount, vertexInRowCount, indexInRowCount, vertices, normals, colors, indices, 3);

	FillPlane(Vector3(-0.5f,  0.5f, -0.5f), Vector3( 1.0f, 0.0f, 0.0f), Vector3( 0.0f, 0.0f, 1.0f),
						  m_levelCount, vertexInRowCount, indexInRowCount, vertices, normals, colors, indices, 4);

	FillPlane(Vector3( 0.5f, -0.5f,  0.5f), Vector3( 0.0f, 0.0f,-1.0f), Vector3(-1.0f, 0.0f, 0.0f),
						  m_levelCount, vertexInRowCount, indexInRowCount, vertices, normals, colors, indices, 5);

	meshImpl->SetVertices(vertices);
	meshImpl->SetNormals(normals);
	meshImpl->SetColors(colors);
	meshImpl->SetIndices(indices, MESH_TOPOLOGY_TRIANGLE_STRIP);
	meshImpl->Apply();
}

void FillCubePlane2(const Vector3 & bottomLeft, const Vector3 & right, const Vector3 & up, int m_levelCount, 
			   int vertexInRowCount, int indexInRowCount, 
			   std::vector<Vector3> & vertices, std::vector<Vector3> & normals, std::vector<Vector4> & colors, std::vector<int> & indices,
			   int planeIndex)
{
	const int iMax = m_levelCount;
	const int jMax = m_levelCount;

	// Initialize vertices
	int vertexShift = planeIndex * vertexInRowCount * m_levelCount;
	for (int j = 0, k = 0; j < jMax; ++j)
	{
		for (int i = 0; i < iMax; ++i)
		{
			// Paint cube in two colors: white and gray
			Vector4 color = ((i + j) % 2 == 0) ? Vector4(1, 1, 1, 1) : Vector4(0.5, 0.5, 0.5, 1);

			int idx0 = vertexShift + (k + 0);
			SetVertexOnPlane(idx0, i + 0, iMax, j + 0, jMax, bottomLeft, right, up, vertices, normals, colors, color);

			int idx1 = vertexShift + (k + 1);
			SetVertexOnPlane(idx1, i + 0, iMax, j + 1, jMax, bottomLeft, right, up, vertices, normals, colors, color);

			int idx2 = vertexShift + (k + 2);
			SetVertexOnPlane(idx2, i + 1, iMax, j + 1, jMax, bottomLeft, right, up, vertices, normals, colors, color);

			int idx3 = vertexShift + (k + 3);
			SetVertexOnPlane(idx3, i + 1, iMax, j + 0, jMax, bottomLeft, right, up, vertices, normals, colors, color);

			k += 4;
		}		
	}
	
	// Initialize indices
	int indexShift = planeIndex * indexInRowCount * m_levelCount;
	for (int j = 0, k = 0, m = 0; j < m_levelCount; ++j)
	{
		for (int i = 0; i < m_levelCount; ++i)
		{
			indices[indexShift + (k + 0)] = vertexShift + (m + 0);
			indices[indexShift + (k + 1)] = vertexShift + (m + 1);
			indices[indexShift + (k + 2)] = vertexShift + (m + 2);

			indices[indexShift + (k + 3)] = vertexShift + (m + 0);
			indices[indexShift + (k + 4)] = vertexShift + (m + 2);
			indices[indexShift + (k + 5)] = vertexShift + (m + 3);

			m += 4;
			k += 6;
		}
	}
}

void MeshCube::InitCubeDetailedList()
{
	int vertexInRowCount	= 4 * m_levelCount;					// (4 vertices per quad) * (quad count in row)
	int vertexInPlaneCount	= vertexInRowCount * m_levelCount;	// (quad count in row)   * (row count)
	int vertexCount			= vertexInPlaneCount * 6;			// (quad count on side)  * (6 sides)
	
	std::vector<Vector3> vertices;
	std::vector<Vector4> colors;
	std::vector<Vector3> normals;	
	std::vector<Vector3> uv0;

	vertices.resize(vertexCount);
	colors.resize(vertexCount);
	normals.resize(vertexCount);	
	uv0.resize(vertexCount);

	
	int indexInRowCount		= 6 * m_levelCount;					// (6 indices per quad)  * (quad count in row)
	int indexInPlaneCount	= indexInRowCount * m_levelCount;	// (index count in row)  * (row count)
	int indexCount			= indexInPlaneCount * 6;			// (index count on side) * (6 sides)

	std::vector<int> indices;
	
	indices.resize(indexCount);
	
	FillCubePlane2(Vector3(-0.5f, -0.5f, -0.5f), Vector3( 1.0f, 0.0f, 0.0f), Vector3( 0.0f, 1.0f, 0.0f),
						  m_levelCount, vertexInRowCount, indexInRowCount, vertices, normals, colors, indices, 0);

	FillCubePlane2(Vector3( 0.5f, -0.5f, -0.5f), Vector3( 0.0f, 0.0f, 1.0f), Vector3( 0.0f, 1.0f, 0.0f),
						  m_levelCount, vertexInRowCount, indexInRowCount, vertices, normals, colors, indices, 1);

	FillCubePlane2(Vector3( 0.5f, -0.5f,  0.5f), Vector3(-1.0f, 0.0f, 0.0f), Vector3( 0.0f, 1.0f, 0.0f),
						  m_levelCount, vertexInRowCount, indexInRowCount, vertices, normals, colors, indices, 2);

	FillCubePlane2(Vector3(-0.5f, -0.5f,  0.5f), Vector3( 0.0f, 0.0f,-1.0f), Vector3( 0.0f, 1.0f, 0.0f),
						  m_levelCount, vertexInRowCount, indexInRowCount, vertices, normals, colors, indices, 3);

	FillCubePlane2(Vector3(-0.5f,  0.5f, -0.5f), Vector3( 1.0f, 0.0f, 0.0f), Vector3( 0.0f, 0.0f, 1.0f),
						  m_levelCount, vertexInRowCount, indexInRowCount, vertices, normals, colors, indices, 4);

	FillCubePlane2(Vector3( 0.5f, -0.5f,  0.5f), Vector3( 0.0f, 0.0f,-1.0f), Vector3(-1.0f, 0.0f, 0.0f),
						  m_levelCount, vertexInRowCount, indexInRowCount, vertices, normals, colors, indices, 5);


	meshImpl->SetVertices(vertices);
	meshImpl->SetColors(colors);
	meshImpl->SetNormals(normals);
	meshImpl->SetUV0(uv0);

	meshImpl->SetIndices(indices, MESH_TOPOLOGY_TRIANGLE_LIST);

	meshImpl->Apply();
}

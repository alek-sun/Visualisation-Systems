#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9.h"
#include "GraphicsEngine/GraphicsApi/MeshImpl.h"


class DX9Mesh : public MeshImpl
{
public:
	void Init();
	void Deinit();

	void Render();

	void SetVertices(const std::vector<Vector3> & vertices);
	void SetNormals (const std::vector<Vector3> & normals);
	void SetColors  (const std::vector<Vector4> & colors);
	void SetIndices	(const std::vector<int> & indices, MeshTopology topology);
	void SetUV0		(const std::vector<Vector3> & uv0);
	
	void Apply();

private:
	HRESULT	CreateVertexBuffer	(void * p_gVertices, UINT size, int vertexCount, DWORD fvf);
	HRESULT	CreateIndexBuffer	(void * p_gIndices,  UINT size, int indexCount, D3DPRIMITIVETYPE primitiveType);

	std::vector<Vector3>	m_vertices;
	std::vector<Vector3>	m_normals;
	std::vector<Vector4>	m_colors;
	std::vector<int>		m_indices;
	MeshTopology			m_topology;
	std::vector<Vector3>	m_uv0;

	LPDIRECT3DDEVICE9		m_pDevice;
	LPDIRECT3DVERTEXBUFFER9	m_pVertexBuffer;
	LPDIRECT3DINDEXBUFFER9	m_pIndexBuffer;
	int						m_verticesCount;
	int						m_indicesCount;
	DWORD					m_fvf;
	D3DPRIMITIVETYPE		m_primitiveType;
	UINT					m_primitiveCount;
	UINT					m_vertexSize;
};

#endif

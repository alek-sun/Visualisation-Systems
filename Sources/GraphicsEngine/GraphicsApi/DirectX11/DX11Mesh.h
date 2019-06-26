#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX11/DX11.h"
#include "GraphicsEngine/GraphicsApi/MeshImpl.h"


class DX11Mesh : public MeshImpl
{
public:
	DX11Mesh();

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
	HRESULT	CreateVertexBuffer	(void * pVertices, UINT size, int vertexCount);
	HRESULT	CreateIndexBuffer	(void * pIndices,  UINT size, int indexCount, D3D_PRIMITIVE_TOPOLOGY primitiveType);

	std::vector<Vector3>	m_vertices;
	std::vector<Vector3>	m_normals;
	std::vector<Vector4>	m_colors;
	std::vector<int>		m_indices;
	MeshTopology			m_topology;
	std::vector<Vector3>	m_uv0;

	ID3D11Device *			m_pDevice;
	ID3D11DeviceContext *	m_pContext;
	ID3D11Buffer *			m_pVertexBuffer;
	ID3D11Buffer*           m_pIndexBuffer;
	

	int						m_verticesCount;
	UINT					m_vertexSize;
	UINT					m_offset;
	int						m_indicesCount;
	D3D_PRIMITIVE_TOPOLOGY	m_primitiveType;
	UINT					m_primitiveCount;	
};

#endif

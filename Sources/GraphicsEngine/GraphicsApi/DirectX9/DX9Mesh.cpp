#include "DX9Mesh.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsApi/DirectX9/DX9GraphicsEngineContext.h"


// A structure for our custom vertex type
struct DX9CUSTOMVERTEX
{
	FLOAT x, y, z;
	FLOAT nx, ny, nz;
	DWORD color; // == (byte r, g, b, a;)
	FLOAT u0, v0;
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 | D3DFVF_TEXCOORDSIZE2(0))


void DX9Mesh::Init()
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX9GraphicsEngineContext * pDX9Context = static_cast<const DX9GraphicsEngineContext *>( pContext );
	m_pDevice = pDX9Context->m_pDevice;
}

void DX9Mesh::Deinit()
{
	if( m_pVertexBuffer != NULL )
        m_pVertexBuffer->Release();
}

void DX9Mesh::Render()
{
	// Render the vertex buffer contents
	m_pDevice->SetStreamSource( 0, m_pVertexBuffer, 0, m_vertexSize );
	m_pDevice->SetFVF( m_fvf );
	m_pDevice->SetIndices( m_pIndexBuffer );
	m_pDevice->DrawIndexedPrimitive( m_primitiveType, 0, 0, m_verticesCount, 0, m_primitiveCount );
}


void DX9Mesh::SetVertices(const std::vector<Vector3> & vertices)
{
	m_vertices = vertices;
}

void DX9Mesh::SetNormals(const std::vector<Vector3> & normals)
{
	m_normals = normals;
}

void DX9Mesh::SetColors(const std::vector<Vector4> & colors)
{
	m_colors = colors;
}

void DX9Mesh::SetIndices(const std::vector<int> & indices, MeshTopology topology)
{
	m_indices	= indices;
	m_topology	= topology;
}

void DX9Mesh::SetUV0(const std::vector<Vector3> & uv0)
{
	m_uv0 = uv0;
}

void DX9Mesh::Apply()
{
	typedef std::vector<Vector3>::size_type size;
	size size1 = m_vertices.size();
	size size2 = m_normals.size();
	//size size3 = m_colors.size();
	
	// TODO: ƒелать Fatal()
	if (size1 != size2)
	{
		return;
	}
	
	std::vector<DX9CUSTOMVERTEX> vertices;
	
	for (size i = 0; i < size1; i++)
	{
		Vector3 v = m_vertices[i];
		Vector3 n = m_normals[i];
		Vector4 c = m_colors[i];
		DWORD color = D3DCOLOR_COLORVALUE(c.x, c.y, c.z, c.w);
		Vector3 uv0 = m_uv0[i];

		DX9CUSTOMVERTEX g_vertex = { (FLOAT) v.x, (FLOAT) v.y, (FLOAT) v.z,
								  (FLOAT) n.x, (FLOAT) n.y, (FLOAT) n.z,
								  color, 
								  (FLOAT) uv0.x, (FLOAT) uv0.y};
		vertices.push_back(g_vertex);
	}

	// TODO: ќбрабатывать возвращаемое значение
	CreateVertexBuffer(&vertices[0], vertices.size() * sizeof(DX9CUSTOMVERTEX), vertices.size(), D3DFVF_CUSTOMVERTEX);

	// TODO: ƒелать Fatal()
	D3DPRIMITIVETYPE primitiveType = (m_topology == MESH_TOPOLOGY_TRIANGLE_LIST) ? D3DPT_TRIANGLELIST : D3DPT_TRIANGLESTRIP;

	// TODO: ќбрабатывать возвращаемое значение
	CreateIndexBuffer (&m_indices[0],  m_indices.size() * sizeof(int), m_indices.size(), primitiveType);
}

HRESULT DX9Mesh::CreateVertexBuffer(void * p_gVertices, UINT vertexArraySize, int vertexCount, DWORD fvf)
{
	m_verticesCount = vertexCount;
	m_fvf = fvf;
	m_vertexSize = vertexArraySize / vertexCount;
	
	// Create the vertex buffer.
	if( FAILED( m_pDevice->CreateVertexBuffer( vertexArraySize, 0, m_fvf, D3DPOOL_MANAGED, &m_pVertexBuffer, NULL ) ) )
	{
	    return E_FAIL;
	}
	
	// Fill the vertex buffer.
	VOID* pVertices;
	if( FAILED( m_pVertexBuffer->Lock( 0, vertexArraySize, ( void** )&pVertices, 0 ) ) )
	{
	    return E_FAIL;
	}
	memcpy( pVertices, p_gVertices, vertexArraySize );
	m_pVertexBuffer->Unlock();
	
	return S_OK;
}

HRESULT	DX9Mesh::CreateIndexBuffer(void * p_gIndices, UINT size, int indexCount, D3DPRIMITIVETYPE primitiveType)
{
	m_primitiveType = primitiveType;
	m_indicesCount = indexCount;

	switch (primitiveType)
	{
	case D3DPT_TRIANGLELIST:
		m_primitiveCount = m_indicesCount / 3;
		break;

	case D3DPT_TRIANGLESTRIP:
		m_primitiveCount = m_indicesCount - 2;
		break;
	}
	
	// Create the index buffer.
	if( FAILED( m_pDevice->CreateIndexBuffer( size, 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_pIndexBuffer, NULL ) ) )
	{
	    return E_FAIL;
	}
	
	// Fill the index buffer.
	VOID* pIndices;
	if( FAILED( m_pIndexBuffer->Lock(0, size, (void**)&pIndices, 0 ) ) )
	{
	    return E_FAIL;
	}
	memcpy( pIndices, p_gIndices, size );
	m_pIndexBuffer->Unlock();
	
	return S_OK;
}

#endif

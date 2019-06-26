#include "DX11Mesh.h"

#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsApi/DirectX11/DX11GraphicsEngineContext.h"


struct DX11CUSTOMVERTEX
{
	DX11CUSTOMVERTEX(FLOAT _x, FLOAT _y, FLOAT _z, 
					FLOAT _nx, FLOAT _ny, FLOAT _nz, 
					FLOAT _r, FLOAT _g, FLOAT _b, FLOAT _a,
					FLOAT _u0, FLOAT _v0)
	{
		x = _x;		y = _y;		z = _z;
		nx = _nx;	ny = _ny;	nz = _nz;
		r = _r;		g = _g;		b = _b; a = _a;
		u0 = _u0;	v0 = _v0;
	}

    FLOAT x, y, z;
	FLOAT nx, ny, nz;
    FLOAT r, g, b, a;
	FLOAT u0, v0;
};


DX11Mesh::DX11Mesh()
	:	m_pDevice		(NULL),
		m_pContext		(NULL),
		m_pVertexBuffer	(NULL),
		m_pIndexBuffer	(NULL)
{
	
}

void DX11Mesh::Init()
{
	const GraphicsEngineContext * pContext = Application::Instance().GetContext();
	const DX11GraphicsEngineContext * pContextDX11 = static_cast<const DX11GraphicsEngineContext *>( pContext );
	m_pDevice = pContextDX11->m_pDevice;
	m_pContext	= pContextDX11->m_pContext;
}

void DX11Mesh::Deinit()
{
	m_pIndexBuffer->Release();
	m_pVertexBuffer->Release();
	m_pVertexBuffer = NULL;
}

void DX11Mesh::Render()
{
	m_pContext->IASetVertexBuffers( 0, 1, &m_pVertexBuffer, &m_vertexSize, &m_offset );
	m_pContext->IASetIndexBuffer( m_pIndexBuffer, DXGI_FORMAT_R32_UINT, 0 );
	m_pContext->IASetPrimitiveTopology( m_primitiveType );
	m_pContext->DrawIndexed( m_indicesCount, 0, 0 );
}

void DX11Mesh::SetVertices(const std::vector<Vector3> & vertices)
{
	m_vertices = vertices;
}

void DX11Mesh::SetNormals(const std::vector<Vector3> & normals)
{
	m_normals = normals;
}

void DX11Mesh::SetColors(const std::vector<Vector4> & colors)
{
	m_colors = colors;
}

void DX11Mesh::SetIndices(const std::vector<int> & indices, MeshTopology topology)
{
	m_indices	= indices;
	m_topology	= topology;
}

void DX11Mesh::SetUV0(const std::vector<Vector3> & uv0)
{
	m_uv0 = uv0;
}

void DX11Mesh::Apply()
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
	
	std::vector<DX11CUSTOMVERTEX> vertices;
	
	for (size i = 0; i < size1; i++)
	{
		Vector3 v = m_vertices[i];
		Vector3 n = m_normals[i];
		Vector4 c = m_colors[i];
		Vector3 uv0 = m_uv0[i];
		
		DX11CUSTOMVERTEX g_vertex = DX11CUSTOMVERTEX( (FLOAT) v.x, (FLOAT) v.y, (FLOAT) v.z,
													  (FLOAT) n.x, (FLOAT) n.y, (FLOAT) n.z,
													  (FLOAT) c.x, (FLOAT) c.y, (FLOAT) c.z, (FLOAT) c.w,
													  (FLOAT) uv0.x, (FLOAT) uv0.y);
		vertices.push_back(g_vertex);
	}
	
	CreateVertexBuffer(&vertices[0], vertices.size() * sizeof(DX11CUSTOMVERTEX), vertices.size());

	// TODO: ƒелать Fatal()
	D3D_PRIMITIVE_TOPOLOGY primitiveType = (m_topology == MESH_TOPOLOGY_TRIANGLE_LIST) ? D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST : D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP;

	// TODO: ќбрабатывать возвращаемое значение
	CreateIndexBuffer (&m_indices[0],  m_indices.size() * sizeof(int), m_indices.size(), primitiveType);	
}

HRESULT DX11Mesh::CreateVertexBuffer(void * pVertices, UINT vertexArraySize, int vertexCount)
{
	m_verticesCount = vertexCount;
	m_vertexSize = vertexArraySize / vertexCount;
	m_offset = 0;
		
	D3D11_BUFFER_DESC bd;
	{
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage			= D3D11_USAGE_DEFAULT;
		//bd.ByteWidth		= sizeof( CUSTOMVERTEX ) * 8;
		bd.ByteWidth		= vertexArraySize;
		bd.BindFlags		= D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags	= 0;
	}

    D3D11_SUBRESOURCE_DATA InitData;
	{
		ZeroMemory( &InitData, sizeof(InitData) );
		InitData.pSysMem = pVertices;
	}

    HRESULT hr = m_pDevice->CreateBuffer( &bd, &InitData, &m_pVertexBuffer );
    if( FAILED( hr ) )
        return hr;
	
	return S_OK;
}

HRESULT	DX11Mesh::CreateIndexBuffer(void * pIndices, UINT size, int indexCount, D3D_PRIMITIVE_TOPOLOGY primitiveType)
{
	m_primitiveType = primitiveType;
	m_indicesCount = indexCount;

	switch (primitiveType)
	{
	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST:
		m_primitiveCount = m_indicesCount / 3;
		break;

	case D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
		m_primitiveCount = m_indicesCount - 2;
		break;
	}
	
	D3D11_BUFFER_DESC bd;
	{
		ZeroMemory( &bd, sizeof(bd) );
		bd.Usage			= D3D11_USAGE_DEFAULT;
		bd.ByteWidth		= size;
		bd.BindFlags		= D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags	= 0;
	}

	D3D11_SUBRESOURCE_DATA InitData;
	{
		ZeroMemory( &InitData, sizeof(InitData) );
		InitData.pSysMem = pIndices;
	}
	
	HRESULT hr = m_pDevice->CreateBuffer( &bd, &InitData, &m_pIndexBuffer );
    if( FAILED( hr ) )
        return hr;
	
	return S_OK;
}

#endif

#include "DX11ConstantBuffer.h"

#ifdef CAN_USE_DIRECT_X


void DX11ConstantBuffer::Init(ID3D11Device * pDevice, ID3D11DeviceContext *	pContext, bool isVertexShader)
{
	m_isVertexShader	= isVertexShader;
	m_pDevice			= pDevice;
	m_pContext			= pContext;
	m_pConstantBuffer	= NULL;
	m_recreateBuffer	= false;
	m_startRegister		= 0;
}

void DX11ConstantBuffer::Deinit()
{
	m_pDevice			= NULL;
	m_pContext			= NULL;

	m_pConstantBuffer->Release();
	m_pConstantBuffer	= NULL;

	m_recreateBuffer	= false;
	m_startRegister		= 0;
}

void DX11ConstantBuffer::SetShaderBegin()
{
	m_startRegister = 0;
}

void DX11ConstantBuffer::SetShaderVector4(const Vector4 & vector)
{
	// Заполняем буфер первый раз ?
	bool first = (m_constantBufferData.size() < m_startRegister + 4);
		
	for (int i = 0; i < 4; ++i)
	{
		if (first)
		{
			m_constantBufferData.push_back( static_cast<const FLOAT>(vector.v[i]) );
			m_recreateBuffer = true;
		}
		else
		{
			m_constantBufferData[m_startRegister + i] = static_cast<const FLOAT>(vector.v[i]);
		}
	}

	m_startRegister += 4;
}

void DX11ConstantBuffer::SetShaderMatrix4x4(const Matrix4x4 & matrix)
{
	// Заполняем буфер первый раз ?
	bool first = (m_constantBufferData.size() < m_startRegister + 16);
		
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (first)
			{
				m_constantBufferData.push_back( static_cast<const FLOAT>(matrix.m[i][j]) );
				m_recreateBuffer = true;
			}
			else
			{
				m_constantBufferData[m_startRegister + i * 4 + j] = static_cast<const FLOAT>(matrix.m[i][j]);
			}
		}
	}

	m_startRegister += 16;
}

void DX11ConstantBuffer::SetShaderEnd()
{
	if (m_recreateBuffer)
	{
		// Delete the constant buffer
		if (NULL != m_pConstantBuffer)
		{
			m_pConstantBuffer->Release();
			m_pConstantBuffer = NULL;
		}

		// Create the constant buffer
		{
			D3D11_BUFFER_DESC bd;
			{
				ZeroMemory( &bd, sizeof(bd) );
				bd.Usage			= D3D11_USAGE_DEFAULT;
				bd.ByteWidth		= m_constantBufferData.size() * sizeof(FLOAT);
				bd.BindFlags		= D3D11_BIND_CONSTANT_BUFFER;
				bd.CPUAccessFlags	= 0;
			}
			
			HRESULT hr = m_pDevice->CreateBuffer( &bd, NULL, &m_pConstantBuffer );
			if( FAILED( hr ) )
				return;
		}

		m_recreateBuffer = false;
	}

	if (m_constantBufferData.size() <= 0) return;

	m_pContext->UpdateSubresource( m_pConstantBuffer, 0, NULL, &m_constantBufferData[0], 0, 0 );
	
	if (m_isVertexShader)
	{
		m_pContext->VSSetConstantBuffers( 0, 1, &m_pConstantBuffer );
	}
	else
	{
		m_pContext->PSSetConstantBuffers( 1, 1, &m_pConstantBuffer );
	}
}

#endif

#pragma once

#include "GraphicsEngine/PlatformApi/Platform.h"
#ifdef CAN_USE_DIRECT_X

#include "GraphicsEngine/GraphicsApi/DirectX9/DX9.h"
#include "GraphicsEngine/GraphicsApi/FixedFunctionPipelineImpl.h"


class DX9FixedFunctionPipeline : public FixedFunctionPipelineImpl
{
public:
	void Init();
	void Deinit();

	void SetMatrixWorld			(const Matrix4x4 & matrix);
	void SetMatrixView			(const Matrix4x4 & matrix);
	void SetMatrixProjection	(const Matrix4x4 & matrix);

private:
	LPDIRECT3DDEVICE9 m_pDevice;
};

#endif

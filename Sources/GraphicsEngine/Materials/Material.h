#pragma once
#include "GraphicsEngine/GraphicsApi/MaterialImpl.h"
#include "GraphicsEngine/Texture2D.h"
#include "GraphicsEngine/RenderTexture.h"
#include <string>


class Object;

namespace RenderQueue
{
	const int SKYBOX	= 1000;
	const int GEOMETRY	= 2000;
};

/**
* @brief Material class is responsible for how the object looks like (how it's rendered).
* It passes all necessary for rendering data to vertex and pixel shaders.
*/
class Material
{
public:
	Material();
	virtual ~Material();

	/**
	* @brief Initialize the material and necessary data here.
	*/
	virtual void	Init();

	/**
	* @brief Deinitialize the material and necessary data here.
	*/
	virtual void	Deinit();

	/**
	* @brief Return true if material was successfully initialized.
	*/
	bool			IsInited();

	/**
	* @brief Pass all necessary for rendering data to vertex and pixel shaders (is called before rendering).
	* @param [in] pObject Pointer to an object that is being rendered now.
	*/
	virtual void SetMaterial(const Object * pObject) = 0;

	/**
	* @brief Clear passed data for rendering (is called after rendering).
	*/
	virtual void ResetMaterial();

	/**
	* @brief Returns render queue (render priority).
	*/
	int GetRenderQueue();

protected:

	/**
	* @brief Should be called once before pass any data to vertex and pixel shaders.
	*/
	void SetMaterialBegin();

#ifndef __GNUC__
#pragma region VERTEX_SHADER_OPERATIONS
#endif
	/**
	* @brief Should be called once before pass any data to the vertex shader.
	*/
	void SetVertexShaderBegin();
	
	/**
	* @brief Pass Matrix4x4 to the vertex shader.
	* @param [in] propertyName Variable name that is declared in the shader.
	* @param [in] matrix Variable value that is passed to the shader.
	*/
	void SetVertexShaderMatrix4x4	(const char * propertyName, const Matrix4x4 & matrix);
	
	/**
	* @brief Pass Vector4 to the vertex shader.
	* @param [in] propertyName Variable name that is declared in the shader.
	* @param [in] vector Variable value that is passed to the shader.
	*/
	void SetVertexShaderVector4		(const char * propertyName, const Vector4 & vector);

	/**
	* @brief Pass Texture2D to the pixel shader.
	* @param [in] propertyName Variable name that is declared in the shader.
	* @param [in] pTexture Variable value that is passed to the shader.
	*/
	void SetVertexShaderTexture2d	(const char * propertyName, const Texture2D * pTexture);
	
	/**
	* @brief Should be called once after pass all data to the vertex shader.
	*/
	void SetVertexShaderEnd();
#ifndef __GNUC__
#pragma endregion
#endif

#ifndef __GNUC__
#pragma region PIXEL_SHADER_OPERATIONS
#endif
	/**
	* @brief Should be called once before pass any data to the pixel shader.
	*/
	void SetPixelShaderBegin();
	
	/**
	* @brief Pass Matrix4x4 to the pixel shader.
	* @param [in] propertyName Variable name that is declared in the shader.
	* @param [in] matrix Variable value that is passed to the shader.
	*/
	void SetPixelShaderMatrix4x4	(const char * propertyName, const Matrix4x4 & matrix);
	
	/**
	* @brief Pass Vector4 to the pixel shader.
	* @param [in] propertyName Variable name that is declared in the shader.
	* @param [in] vector Variable value that is passed to the shader.
	*/
	void SetPixelShaderVector4		(const char * propertyName, const Vector4 & vector);
	
	/**
	* @brief Pass Texture2D to the pixel shader.
	* @param [in] propertyName Variable name that is declared in the shader.
	* @param [in] pTexture Variable value that is passed to the shader.
	*/
	void SetPixelShaderTexture2d	(const char * propertyName, const Texture2D * pTexture);
	
	/**
	* @brief Pass RenderTexture to the pixel shader.
	* @param [in] propertyName Variable name that is declared in the shader.
	* @param [in] pTexture Variable value that is passed to the shader.
	*/
	void SetPixelShaderTexture2d	(const char * propertyName, const RenderTexture * pTexture);
	
	/**
	* @brief Should be called once after pass all data to the pixel shader.
	*/
	void SetPixelShaderEnd();
#ifndef __GNUC__
#pragma endregion
#endif

	/**
	* @brief Should be called once after pass all data to vertex and pixel shaders.
	*/
	void SetMaterialEnd();

	/**
	* @brief File name of the vertex shader source file.
	*/
	std::string		m_vsFileName;

	/**
	* @brief File name of the pixel shader source file.
	*/
	std::string		m_psFileName;

	/**
	* @brief Render queue of the material.
	* It specifies a group of objects with the same render priority.
	* As less this value as earlier this object will be rendered.
	*/
	int m_renderQueue;

private:

	/**
	* @brief Graphics API dependent implementation of the material (e.g. DirectX 9 / DirectX 11 / OpenGL 2.0).
	*/
	MaterialImpl *	m_pImpl;
};

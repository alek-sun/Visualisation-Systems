#pragma once
#include "GraphicsEngine/GraphicsApi/Texture2DImpl.h"



class Texture2D
{
public:
	Texture2D(const char * filepath);
	~Texture2D();

	/**
	* @brief Set texture filter mode (Point, Bilinear, Trilinear, Anisotropic).
	* @param [in] filterMode Texture filter mode.
	*/
	void SetFilterMode(TextureFilterMode filterMode);

	/**
	* @brief Set texture wrap mode (Clamp, Repeat)
	* @param [in] wrapMode Texture wrap mode.
	*/
	void SetWrapMode(TextureWrapMode wrapMode);
		
	const Texture2DImpl * GetImplPointer() const;
	
	/**
	* @brief Pass texture to the pixel shader.
	* @param [in] textureRegister Position number in whole list of textures for the pixel shader.
	* @param [in] toPixelShader If is called from pixel shader then true, from vertex shader - false.
	*/
	void PassToShader(int textureRegister, bool toPixelShader = true) const;

private:
	Texture2DImpl * pImpl;
};

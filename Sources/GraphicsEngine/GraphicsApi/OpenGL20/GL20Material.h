#pragma once
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"
#include "GraphicsEngine/GraphicsApi/MaterialImpl.h"
#include "GraphicsEngine/Matrix4x4.h"
#include <string>


class GL20Material : public MaterialImpl
{
public:
	GL20Material(const char * vertexShaderFilePath, const char * fragmentShaderFilePath);
	~GL20Material();
	
	void Init();
	void Deinit();
	bool IsInited();

	void SetMaterialBegin();
	
	void SetVertexShaderBegin();
	void SetVertexShaderMatrix4x4	(const char * propertyName, const Matrix4x4 & matrix);
	void SetVertexShaderVector4		(const char * propertyName, const Vector4 & vector);
	void SetVertexShaderTexture2d	(const char * propertyName, const Texture2D * pTexture);
	void SetVertexShaderEnd();

	void SetPixelShaderBegin();
	void SetPixelShaderMatrix4x4	(const char * propertyName, const Matrix4x4 & matrix);
	void SetPixelShaderVector4		(const char * propertyName, const Vector4 & vector);
	void SetPixelShaderTexture2d	(const char * propertyName, const Texture2D * pTexture);
	void SetPixelShaderTexture2d	(const char * propertyName, const RenderTexture * pTexture);
	void SetPixelShaderEnd();

	void SetMaterialEnd();

	void ResetMaterial();
	
private:
	void LogErrorInLoadFile(const std::string & filePath);
	void LogErrorInVertexShader();
	void LogErrorInFragmentShader();
	void LogErrorInProgram();
	void LogError(const char * text, const char * filePath = NULL);
	
	bool m_isInited;

	GLuint m_vertexShader;
	GLuint m_fragmentShader;
	GLuint m_program;

	int m_textureRegister;

	std::string		m_vsPath;
	std::string		m_fsPath;
};

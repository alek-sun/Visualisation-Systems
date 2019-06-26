#include "GL20Material.h"
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20Convert.h"
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20RenderTexture.h"
#include "GraphicsEngine/File.h"
#include <iostream>


GL20Material::GL20Material(const char * vertexShaderFilePath, const char * fragmentShaderFilePath)
{
	m_isInited = false;
	
	GLint success = GL_FALSE;

	{
		std::string shadersDirectory = Application::Instance().GetShadersDirectory();
		m_vsPath = shadersDirectory + "GL20/" + std::string(vertexShaderFilePath)   + ".vs";
		m_fsPath = shadersDirectory + "GL20/" + std::string(fragmentShaderFilePath) + ".fs";
	}

	// Vertex shader load and compilation
	{
		if (!File::Exists(m_vsPath))
		{
			LogErrorInLoadFile(m_vsPath);
			return;
		}

		// Load shader text from file
		std::string vsText = File::ReadAllText(m_vsPath);
		const char * pStr = vsText.c_str();
		
		m_vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource (m_vertexShader, 1, &pStr, NULL);
		glCompileShader(m_vertexShader);

		// Check for errors
		glGetShaderiv  (m_vertexShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			LogErrorInVertexShader();
			return;
		}
	}

	// Fragment shader load and compilation
	{
		if (!File::Exists(m_fsPath))
		{
			LogErrorInLoadFile(m_fsPath);
			return;
		}

		// Load shader text from file
		std::string fsText = File::ReadAllText(m_fsPath);
		const char * pStr = fsText.c_str();

		m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource (m_fragmentShader, 1, &pStr, NULL);
		glCompileShader(m_fragmentShader);

		// Check for errors
		glGetShaderiv  (m_fragmentShader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			LogErrorInFragmentShader();
			return;
		}
	}
	
	// Create program and attach vertex and fragment shaders
	{
		m_program = glCreateProgram();
		glAttachShader(m_program, m_vertexShader);
		glAttachShader(m_program, m_fragmentShader);
	}

	// Set order of vertex structure (position, color, normal, texcoords, ...) for vertex shader
	{
		glBindAttribLocation(m_program, 0, "position");
		glBindAttribLocation(m_program, 1, "color");
		glBindAttribLocation(m_program, 2, "normal");
		glBindAttribLocation(m_program, 3, "texcoord0");
	}

	// Link program
	{
		glLinkProgram (m_program);

		// Check for errors
		glGetProgramiv(m_program, GL_LINK_STATUS, &success);	
		if (!success)
		{
			LogErrorInProgram();
			return;
		}
	}

	// Validate program
	{
		glValidateProgram(m_program);
		
		// Check for errors
		glGetProgramiv(m_program, GL_VALIDATE_STATUS, &success);
		if (!success)
		{
			LogErrorInProgram();
		}
	}

	m_isInited = true;
}

GL20Material::~GL20Material()
{
	Deinit();
}

void GL20Material::Init()
{

}

void GL20Material::Deinit()
{
	glDetachShader(m_program, m_vertexShader);
	glDetachShader(m_program, m_fragmentShader);

	glDeleteProgram(m_program);

	glDeleteShader(m_fragmentShader);
	glDeleteShader(m_vertexShader);
}

bool GL20Material::IsInited()
{
	return m_isInited;
}

void GL20Material::SetMaterialBegin()
{
	glUseProgram(m_program);
}

void GL20Material::SetMaterialEnd()
{

}

void GL20Material::ResetMaterial()
{
	glUseProgram(NULL);
}

void GL20Material::SetVertexShaderBegin()
{
	m_textureRegister = 0;
}

void GL20Material::SetVertexShaderMatrix4x4(const char * propertyName, const Matrix4x4 & matrix)
{
	GLuint location = glGetUniformLocation(m_program, propertyName);

	GLfloat matrixf[16];
	GL20Convert::ToGL20Matrix4x4(matrix, matrixf);

	glUniformMatrix4fv(location, 1, GL_FALSE, &matrixf[0]);
}

void GL20Material::SetVertexShaderVector4(const char * propertyName, const Vector4 & vector)
{
	GLuint location = glGetUniformLocation(m_program, propertyName);
	
	GLfloat vectorf[4];	
	GL20Convert::ToGL20Vector4(vector, vectorf);

	glUniform4fv(location, 1, &vectorf[0]);
}

void GL20Material::SetVertexShaderTexture2d(const char * propertyName, const Texture2D * pTexture)
{
	GLuint location = glGetUniformLocation(m_program, propertyName);
	glUniform1i(location, m_textureRegister);
	
	pTexture->PassToShader( m_textureRegister, false );
	
	m_textureRegister += 1;
}

void GL20Material::SetVertexShaderEnd()
{

}

void GL20Material::SetPixelShaderBegin()
{
	m_textureRegister = 0;
}

void GL20Material::SetPixelShaderMatrix4x4(const char * propertyName, const Matrix4x4 & matrix)
{
	GLuint location = glGetUniformLocation(m_program, propertyName);

	GLfloat matrixf[16];
	GL20Convert::ToGL20Matrix4x4(matrix, matrixf);

	glUniformMatrix4fv(location, 1, GL_FALSE, &matrixf[0]);
}

void GL20Material::SetPixelShaderVector4(const char * propertyName, const Vector4 & vector)
{
	GLuint location = glGetUniformLocation(m_program, propertyName);
	
	GLfloat vectorf[4];	
	GL20Convert::ToGL20Vector4(vector, vectorf);

	glUniform4fv(location, 1, &vectorf[0]);
}

void GL20Material::SetPixelShaderTexture2d(const char * propertyName, const Texture2D * pTexture)
{
	GLuint location = glGetUniformLocation(m_program, propertyName);
	glUniform1i(location, m_textureRegister);
	
	pTexture->PassToShader( m_textureRegister, true );
	
	m_textureRegister += 1;
}

void GL20Material::SetPixelShaderTexture2d(const char * propertyName, const RenderTexture * pTexture)
{
	GLuint location = glGetUniformLocation(m_program, propertyName);
	glUniform1i(location, m_textureRegister);
	
	const GL20RenderTexture * pGL20Texture = static_cast<const GL20RenderTexture *>(pTexture->GetImplPointer());
	pGL20Texture->SetTexture(m_textureRegister);

	m_textureRegister += 1;
}

void GL20Material::SetPixelShaderEnd()
{

}

void GL20Material::LogErrorInLoadFile(const std::string & filePath)
{
	std::string text = "ERROR: File " + filePath + " was not found";
	LogError(text.c_str());
}

void GL20Material::LogErrorInVertexShader()
{
	const int MAX_INFO_LOG_SIZE = 4096;
	GLchar text[MAX_INFO_LOG_SIZE];
	
	glGetShaderInfoLog(m_vertexShader, MAX_INFO_LOG_SIZE, NULL, text);
	
	LogError(text, m_vsPath.c_str());
}

void GL20Material::LogErrorInFragmentShader()
{
	const int MAX_INFO_LOG_SIZE = 4096;
	GLchar text[MAX_INFO_LOG_SIZE];
	
	glGetShaderInfoLog(m_fragmentShader, MAX_INFO_LOG_SIZE, NULL, text);
	
	LogError(text, m_fsPath.c_str());
}

void GL20Material::LogErrorInProgram()
{
	const int MAX_INFO_LOG_SIZE = 4096;
	GLchar text[MAX_INFO_LOG_SIZE];

	glGetProgramInfoLog(m_program, MAX_INFO_LOG_SIZE, NULL, text);

	LogError(text);
}

void GL20Material::LogError(const char * text, const char * filePath)
{	
	if (NULL != text)
	{
		std::string title = "Error";
		if (NULL != filePath)
		{
			title += " in " + File::GetFileName(filePath);
		}
        std::cerr << title.c_str() << std::endl;
        std::cerr << text << std::endl;
	}
}

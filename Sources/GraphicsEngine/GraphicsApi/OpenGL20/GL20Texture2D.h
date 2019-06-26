#pragma once
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"
#include "GraphicsEngine/GraphicsApi/Texture2DImpl.h"


// Read more
// http://www.learnopengles.com/android-lesson-six-an-introduction-to-texture-filtering/
// https://www.opengl.org/wiki/Sampler_Object
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/
// http://opengl-master.ru/view_post.php?id=78
// http://www.araku.ac.ir/~d_comp_engineering/88892/1323108/OpenGL%20Game%20Development.pdf


/**
* @brief DX9Texture2D class is the implementation of the 2d-texture in OpenGL 2.0.
*/
class GL20Texture2D : public Texture2DImpl
{
public:
	/**
	* @brief Constructs the object.
	* @param [in] filepath Full path of the file with the texture to load.
	*/
	GL20Texture2D(const char * filepath);

	/**
	* @brief Release resources.
	*/
	~GL20Texture2D();

	/**
	* @brief Pass texture to the pixel shader.
	* @param [in] textureRegister Position number in whole list of textures for the pixel shader.
	* @param [in] toPixelShader If is called from pixel shader then true, from vertex shader - false.
	*/
	void PassToShader(int textureRegister, bool toPixelShader) const;

private:
	GLuint	m_texture;
	int		m_width;
	int		m_height;
};

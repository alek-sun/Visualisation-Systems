#include "GL20GraphicsDevice.h"


void GL20GraphicsDevice::SetFillMode( FillMode fillMode )
{

	if (fillMode == FILL_MODE_SOLID)
	{
		// Draw polygons only (is used usual)
		glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
	}
	else if (fillMode == FILL_MODE_WIREFRAME)
	{
		// Draw edges only (is used for debug)
		glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
	}
}

void GL20GraphicsDevice::SetZWrite( bool enable )
{
	// https://www.opengl.org/sdk/docs/man/docbook4/xhtml/glDepthMask.xml
	// https://www.opengl.org/discussion_boards/showthread.php/175878-enable-depth-test-but-disable-write

	if (enable)
	{
		glDepthMask( GL_TRUE );
		glDepthFunc( GL_LESS );
	}
	else
	{
		glDepthMask( GL_FALSE );
		glDepthFunc( GL_ALWAYS );
	}
}

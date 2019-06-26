#version 110

attribute vec3 position;
attribute vec4 color;
attribute vec3 texcoord0;

varying vec2 uv1;
uniform vec4 constColor;
uniform mat4 matrixWorldViewProjT;

void main()
{
	//gl_Position = matrixWorldViewProjT * vec4(position, 1.0);	// OpenGL
	gl_Position = vec4(position, 1.0) * matrixWorldViewProjT;	// DirectX
	gl_FrontColor = color * constColor;
	uv1	= texcoord0.xy;
}
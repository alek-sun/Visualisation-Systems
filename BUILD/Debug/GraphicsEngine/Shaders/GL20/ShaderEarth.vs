#version 110

// Shader parameters
uniform mat4 matrixWorldViewProjT;

// Vertex structure
attribute vec3 position;
attribute vec4 color;
attribute vec3 normal;
attribute vec3 texcoord0;

varying vec3 localPosition;
varying vec3 localNormal;

varying vec2 uv1;

void main()
{
	gl_Position		= vec4(position, 1.0) * matrixWorldViewProjT;
	gl_FrontColor	= color;
	localPosition	= position;
	localNormal		= normal;
	uv1				= texcoord0.xy;
}
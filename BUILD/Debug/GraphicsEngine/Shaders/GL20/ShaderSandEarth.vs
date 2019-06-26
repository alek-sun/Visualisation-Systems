#version 110

attribute vec3 position;
attribute vec4 color;
attribute vec3 normal;
attribute vec3 texcoord0;

uniform vec4 constColor;
uniform mat4 matrixWorldViewProjT;

varying vec2 uv1;

void main()
{
	gl_Position		= vec4(position, 1.0) * matrixWorldViewProjT;
	gl_FrontColor	= color * constColor;
	uv1				= texcoord0.xy;
}
#version 110

// Vertex structure
// Set order of vertex structure (position, color)
// Search in C++ code funciton GL20Mesh::Render()
// glVertexAttribPointer(0, ...) // this is "position"
// glVertexAttribPointer(1, ...) // this is "color"
attribute vec3 position;
attribute vec4 color;

// Shader parameters
// Search in C++ code functions like "glUniform4"
// i.e. functions: glUniform4fv(), glUniformMatrix4fv().
// These functions pass to shader parameters listed below
uniform vec4 time;
uniform vec4 constColor;
uniform mat4 matrixWorldViewProjT;

void main()
{
	float t = abs(cos(time.x));
	vec3 p1 = position;
	vec3 p2 = normalize(position)/3.;
	vec3 p = p1 * (1.0 - t) + p2 * t;
	gl_Position = vec4(p, 1.0) * matrixWorldViewProjT;
	gl_FrontColor = constColor*color;
}
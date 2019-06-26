#pragma once
#include "GraphicsEngine/GraphicsApi/OpenGL20/GL20.h"
#include "GraphicsEngine/GraphicsApi/MeshImpl.h"


class GL20Mesh : public MeshImpl
{
public:
	GL20Mesh();

	void Init();
	void Deinit();

	void Render();

	void SetVertices(const std::vector<Vector3> & vertices);
	void SetNormals (const std::vector<Vector3> & normals);
	void SetColors  (const std::vector<Vector4> & colors);
	void SetIndices	(const std::vector<int> & indices, MeshTopology topology);
	void SetUV0		(const std::vector<Vector3> & uv0);
	
	void Apply();

private:
	void CreatePositionBuffer();
	void CreateColorBuffer();
	void CreateNormalBuffer();
	void CreateUV0();

	std::vector<Vector3>	m_vertices;
	std::vector<Vector3>	m_normals;
	std::vector<Vector4>	m_colors;
	std::vector<GLuint>		m_indices;
	MeshTopology			m_topology;
	std::vector<Vector3>	m_uv0;

	GLuint	m_bufferPosition;
	GLuint	m_bufferColor;
	GLuint	m_bufferNormal;
	GLuint	m_bufferUV0;
	GLenum	m_primitiveType;
	GLsizei	m_indicesCount;
};

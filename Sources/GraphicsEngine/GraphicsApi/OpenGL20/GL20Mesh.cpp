#include "GL20Mesh.h"


GL20Mesh::GL20Mesh()
{

}

void GL20Mesh::Init()
{

}

void GL20Mesh::Deinit()
{
	glDeleteBuffers(1, &m_bufferNormal);
	glDeleteBuffers(1, &m_bufferColor);
	glDeleteBuffers(1, &m_bufferPosition);
}

void GL20Mesh::Render()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
		
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferPosition);
	glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferColor);
	glVertexAttribPointer(1, 4, GL_DOUBLE, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferNormal);
	glVertexAttribPointer(2, 3, GL_DOUBLE, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_bufferUV0);
	glVertexAttribPointer(3, 3, GL_DOUBLE, GL_FALSE, 0, 0);

	glDrawElements(m_primitiveType, m_indicesCount, GL_UNSIGNED_INT, &m_indices[0]);

	glDisableVertexAttribArray(3);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);


	glUseProgram(0);
}

void GL20Mesh::SetVertices(const std::vector<Vector3> & vertices)
{
	m_vertices = vertices;
}

void GL20Mesh::SetNormals(const std::vector<Vector3> & normals)
{
	m_normals = normals;
}

void GL20Mesh::SetColors(const std::vector<Vector4> & colors)
{
	m_colors = colors;
}

void GL20Mesh::SetIndices(const std::vector<int> & indices, MeshTopology topology)
{
	m_indicesCount = indices.size();
	m_indices.reserve(m_indicesCount);

	for (GLsizei i = 0; i < m_indicesCount; ++i)
	{
		m_indices.push_back( static_cast<GLuint>(indices[i]) );
	}
	
	m_topology	= topology;
}

void GL20Mesh::SetUV0(const std::vector<Vector3> & uv0)
{
	m_uv0 = uv0;
}

void GL20Mesh::Apply()
{
	CreatePositionBuffer();
	CreateColorBuffer();
	CreateNormalBuffer();
	CreateUV0();

	m_primitiveType = (m_topology == MESH_TOPOLOGY_TRIANGLE_LIST) ?  GL_TRIANGLES :  GL_TRIANGLE_STRIP;
}

void GL20Mesh::CreatePositionBuffer()
{
	glGenBuffers(1, &m_bufferPosition);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferPosition);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_vertices.size(), &m_vertices[0], GL_STATIC_DRAW);
}

void GL20Mesh::CreateColorBuffer()
{
	glGenBuffers(1, &m_bufferColor);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferColor);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector4) * m_colors.size(), &m_colors[0], GL_STATIC_DRAW);
}

void GL20Mesh::CreateNormalBuffer()
{
	glGenBuffers(1, &m_bufferNormal);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferNormal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_normals.size(), &m_normals[0], GL_STATIC_DRAW);
}

void GL20Mesh::CreateUV0()
{
	glGenBuffers(1, &m_bufferUV0);
	glBindBuffer(GL_ARRAY_BUFFER, m_bufferUV0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * m_uv0.size(), &m_uv0[0], GL_STATIC_DRAW);
}

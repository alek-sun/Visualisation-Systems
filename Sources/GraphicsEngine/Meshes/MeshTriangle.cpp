#include "MeshTriangle.h"


void MeshTriangle::Init()
{
	Mesh::Init();

	std::vector<Vector3> vertices;
	vertices.push_back( Vector3( 1.0f,-1.0f, 0.0f) );
	vertices.push_back( Vector3(-1.0f,-1.0f, 0.0f) );
	vertices.push_back( Vector3( 0.0f, 1.0f, 0.0f) );

	std::vector<Vector4> colors;
	colors.push_back( Vector4(1.0f, 0.0f, 0.0f, 1.0f) );
	colors.push_back( Vector4(0.0f, 1.0f, 0.0f, 1.0f) );
	colors.push_back( Vector4(0.0f, 0.0f, 1.0f, 1.0f) );
	
	std::vector<Vector3> normals;
	normals.push_back( Vector3(0.0f, 0.0f, -1.0f) );
	normals.push_back( Vector3(0.0f, 0.0f, -1.0f) );
	normals.push_back( Vector3(0.0f, 0.0f, -1.0f) );
	
	std::vector<Vector3> uv0;
	uv0.push_back( Vector3(1.0f, 0.0f, 0.0f) );
	uv0.push_back( Vector3(0.0f, 0.0f, 0.0f) );
	uv0.push_back( Vector3(0.5f, 0.5f, 0.0f) );

	std::vector<int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);


	meshImpl->SetVertices(vertices);
	meshImpl->SetNormals(normals);
	meshImpl->SetColors(colors);
	meshImpl->SetUV0(uv0);

	meshImpl->SetIndices(indices, MESH_TOPOLOGY_TRIANGLE_LIST);

	meshImpl->Apply();
}

void MeshTriangle::Deinit()
{
	Mesh::Deinit();
}

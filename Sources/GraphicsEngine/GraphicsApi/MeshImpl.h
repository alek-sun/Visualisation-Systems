#pragma once
#include <vector>
#include "GraphicsEngine/Vector3.h"
#include "GraphicsEngine/Vector4.h"


enum MeshTopology
{
	MESH_TOPOLOGY_TRIANGLE_LIST,
	MESH_TOPOLOGY_TRIANGLE_STRIP
};


// Interface for a mesh.
// Subclasses implement the interface over concrete Graphics API.
// Design Patterns: Strategy (role - Strategy) or Bridge (role - Implementor) or Abstract Factory (role - Abstract Product).
class MeshImpl
{
public:
	// TODO: ѕроверить, что декструкторы virtual у всех классов ...Impl
	// TODO: –азобратьс¤ с возвращаемым значением
	virtual void Init() = 0;
	virtual void Deinit() = 0;
	virtual void Render() = 0;

	virtual void SetVertices(const std::vector<Vector3> & vertices) = 0;
	virtual void SetNormals	(const std::vector<Vector3> & normals) = 0;
	virtual void SetColors	(const std::vector<Vector4> & colors) = 0;
	virtual void SetIndices	(const std::vector<int> & indices, MeshTopology topology) = 0;
	virtual void SetUV0		(const std::vector<Vector3> & uv0) = 0;
	
	virtual void Apply() = 0;
};

#pragma once
#include "Mesh.h"


// Design Patterns: Bridge (role - RefinedAbstraction).
class MeshQuad : public Mesh
{
public:
	virtual void Init();
	virtual void Deinit();
};

#pragma once
#include "Mesh.h"


class MeshPlane : public Mesh
{
public:
	MeshPlane(int levelCount = 1);

	virtual void Init();
	virtual void Deinit();

private:
	void InitCubeSimple();
	void InitCubeDetailedStrip();
	void InitCubeDetailedList();	

	int m_levelCount;	
};
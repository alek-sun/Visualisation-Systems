#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Meshes/MeshQuad.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Light.h"
#include "GraphicsEngine/Materials/MaterialRoad.h"

#include "Tasks/Task.h"


/**
* @brief Shows how to map 3 textures to one plane mesh.
* Key code is situated in the classes MaterialRoad, MeshQuad.
*/
class Task05_02: public Task
{
public:
	virtual ~Task05_02() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
	
		// Camera
		{
			Object * pCameraObj = new Object();
			Camera * pCamera = new Camera();
			pCameraObj->m_pTransform = new Transform( Vector3(0.0f, 0.2f,-5.0f), Vector3(10.0f, 0.0f, 0.0f) );		
			pCameraObj->AddComponent( pCamera );

			scene.SetCamera( pCamera );
		}

		// Object #1 - Road with 3 textures
		{
			Object * pObject1 = new Object();

			pObject1->m_pTransform	= new Transform( 0,0,0, 0,0,0, 1,1,10 );
			pObject1->m_pMesh		= new MeshQuad();			
			pObject1->m_pMaterial	= new MaterialRoad(Vector3(0.5, 0.5, 0.5));
			scene.AddObject( pObject1 );
		}
	}

	virtual void Update()
	{
		
	}
};

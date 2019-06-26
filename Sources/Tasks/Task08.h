#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Meshes/MeshQuad.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Materials/MaterialUnlit.h"
#include "GraphicsEngine/Light.h"

#include "Tasks/Task.h"
#include "Tasks/CameraController.h"


/**
* @brief Shows how to process user's input (keyboard and mouse).
* Key code is situated in the classes CameraController, Input, IternalInput, WinInput, GL20Input.
*/
class Task08: public Task
{
public:
	virtual ~Task08() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
	
		// Camera
		{
			Object * pCameraObj = new Object();
			Camera * pCamera = new Camera();
			pCameraObj->m_pTransform = new Transform( Vector3(0.0f, 0.5f,-5.0f), Vector3(0.0f, 0.0f, 0.0f) );
			pCameraObj->AddComponent( pCamera );
			pCameraObj->AddComponent(new CameraController());
			pCameraObj->AddComponent(new CameraController());

			scene.SetCamera( pCamera );
		}

		// Object #1 - Road with 3 textures
		{
			Object * pObject1 = new Object();

			pObject1->m_pTransform	= new Transform( 0,0,0, 0,0,0, 1,1,10 );
			pObject1->m_pMesh		= new MeshQuad();			
			pObject1->m_pMaterial	= new MaterialUnlit(Vector3(0.5, 0.5, 0.5));
						
			scene.AddObject( pObject1 );
		}
		// Object #2 - Cylinder (is twisted)
		{
			Object * pObject = new Object();
			pObject->m_pTransform = new Transform(Vector3(20, 0, 0), Vector3(0, 30, 0));
			pObject->m_pMesh = new MeshCylinder(20);
			pObject->m_pMaterial = new MaterialUnlitSimpleCyl();

			scene.AddObject(pObject);
		}
	}

	virtual void Update()
	{
	
	}
};

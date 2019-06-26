#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Meshes/MeshObjFile.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Materials/MaterialDiffuse.h"
#include "GraphicsEngine/Light.h"

#include "Tasks/Task.h"
#include "Tasks/ObjectRotator.h"


/**
* @brief Shows how to load mesh from obj-file.
* Key code is situated in the class MeshObjFile.
*/
class Task07: public Task
{
public:
	virtual ~Task07() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
	
		// Camera
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform( Vector3(0.0f, 4.0f, -10.0f),
				Vector3(20.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCameraObj->AddComponent( pCamera );

			scene.SetCamera( pCamera );
		}

		// Object #1 - Earth
		{
			Object * pObject1 = new Object();
			//pObject1->m_pMesh		= new MeshObjFile("MeshCube.obj");
			//pObject1->m_pMesh		= new MeshObjFile("MeshSphere.obj");
			pObject1->m_pMesh		= new MeshObjFile("MeshHouse.obj");
			pObject1->m_pTransform	= new Transform(0,0,0, 0,0,0, 1,1,1);
			pObject1->m_pMaterial	= new MaterialDiffuse();
			pObject1->AddComponent( new ObjectRotator(0,45,0) );
						
			scene.AddObject( pObject1 );
		}

		// Lightsource #1 - Directional
		{
			Light * pLight = new Light(LIGHT_DIRECTIONAL);
			pLight->SetColor(1,1,1);
			pLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->m_pTransform	= new Transform(1,0,0, 45,90,0, 1,1,1);
			pLightObject->AddComponent(pLight);
			
			scene.AddLight(pLight);
		}
	}

	virtual void Update()
	{
		
	}
};

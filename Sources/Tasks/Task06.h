#pragma once
#include "Tasks/ObjectRotator.h"
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Meshes/MeshSphere.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Light.h"
#include "GraphicsEngine/Materials/MaterialEarth.h"
#include "Tasks/Task.h"


/**
* @brief Shows how to write bumped material.
* Key code is situated in the class MaterialBumpedSpecular.
*/
class Task06: public Task
{
public:
	virtual ~Task06() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
	
		// Camera
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform( Vector3(0.0f, 0.0f,-1.5f),
				Vector3(0.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCameraObj->AddComponent( pCamera );

			scene.SetCamera( pCamera );
		}

		// Object #1 - Earth
		{
			Object * pObject1 = new Object();

			pObject1->m_pMesh		= new MeshSphere(30);
			pObject1->m_pTransform	= new Transform(0,0,0, 0,0,0, 1,1,1);
            pObject1->m_pMaterial	= new MaterialEarth(TEXTURE_FILTER_MODE_ANISOTROPIC);
			pObject1->AddComponent( new ObjectRotator(0, 20, 0) );
						
			scene.AddObject( pObject1 );
		}

		// Light source #1 - Directional
		{
			Light * pLight = new Light(LIGHT_DIRECTIONAL);
			pLight->SetColor(1,1,1);
			pLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->m_pTransform	= new Transform(10,5,0,70,5,0, 1,1,1);
			pLightObject->AddComponent(pLight);
			pLightObject->AddComponent( new ObjectRotator(0.3f,0,0) );

			scene.AddLight(pLight);
		}
	}

	virtual void Update()
	{
		
	}
};

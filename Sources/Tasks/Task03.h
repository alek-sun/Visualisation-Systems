#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Materials/MaterialUnlitSimple.h"
#include "GraphicsEngine/Meshes/MeshCube.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Materials/MyMaterialDiffuse.h"
#include "GraphicsEngine/Meshes/MeshSphere.h"
#include "GraphicsEngine/Meshes/MeshCube.h"
#include "GraphicsEngine/Materials/MaterialUnlitSimpleCube.h"
#include "GraphicsEngine/Light.h"
#include "GraphicsEngine/Materials/MyMaterialDiffuse.h"

#include "Tasks/Task.h"
#include "Tasks/FpsCounter.h"
#include "Tasks/ObjectRotator.h"


/**
* @brief Shows how to write text to the screen.
* Key code is situated in the classes FpsCounter, GUI, InternalGUI, DX9GUI, GL20GUI.
*/
class Task03: public Task
{
public:
	virtual ~Task03() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
	
		// Camera
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform( Vector3(0, 3, -10), Vector3(20.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCamera->SetFovY(90);
			pCamera->SetNearPlane(0.01f);
			pCamera->SetFarPlane(100);
			pCameraObj->AddComponent( pCamera );

			scene.SetCamera( pCamera );
		}

		// Object - Sphere
		{
			Object * pObject1 = new Object();

			pObject1->m_pTransform = new Transform(5, 0, 0, 0, 0, 0, 4, 2, 3);
			pObject1->m_pMesh = new MeshSphere(20);
			pObject1->m_pMaterial = new MyMaterialDiffuse();
			pObject1->AddComponent(new ObjectRotator(200, 100, 700));

			scene.AddObject(pObject1);
		}

		// Object - Sphere
		{
			Object * pObject1 = new Object();

			pObject1->m_pTransform = new Transform(0, -5, 0, 0, 0, 0, 4, 7, 3);
			pObject1->m_pMesh = new MeshSphere(20);
			pObject1->m_pMaterial = new MyMaterialDiffuse();
			pObject1->AddComponent(new ObjectRotator(220, 800, 340));

			scene.AddObject(pObject1);
		}

		// Object - Sphere
		{
			Object * pObject1 = new Object();

			pObject1->m_pTransform = new Transform(0, 5, 0, 0, 0, 0, 2, 2, 6);
			pObject1->m_pMesh = new MeshSphere(20);
			pObject1->m_pMaterial = new MyMaterialDiffuse();
			pObject1->AddComponent(new ObjectRotator(120, 600, 540));

			scene.AddObject(pObject1);
		}

		// Object - Sphere
		{
			Object * pObject1 = new Object();

			pObject1->m_pTransform = new Transform(-6, -5, 0, 0, 0, 0, 4, 7, 8);
			pObject1->m_pMesh = new MeshSphere(20);
			pObject1->m_pMaterial = new MyMaterialDiffuse();
			pObject1->AddComponent(new ObjectRotator(420, 200, 540));

			scene.AddObject(pObject1);
		}
		//cube
		{
			Object * pObject = new Object();
			pObject->m_pTransform = new Transform(Vector3(-5, 2, 0), Vector3(0, 0, 0), Vector3(5, 5, 5));
			pObject->m_pMesh = new MeshCube(10);
			pObject->m_pMaterial = new MaterialUnlitSimpleCube();

			scene.AddObject(pObject);
		}

		// Ligth source #1 - Directional
		{
			Light * pLight = new Light(LIGHT_DIRECTIONAL);
			pLight->SetColor(0.6, 0, 0.9);
			pLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->m_pTransform = new Transform(0, 0, 0, -90, -140, 0, 1, 1, 1);
			pLightObject->AddComponent(pLight);

			scene.AddLight(pLight);
		}

		// Ligth source #2 - Point
		{
			Light * pLight = new Light(LIGHT_POINT);
			pLight->SetColor(0, 0.5, 1);
			pLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->m_pTransform = new Transform(-30, 0, 0, 0, 0, 0, 1, 1, 1);
			pLightObject->AddComponent(pLight);

			scene.AddLight(pLight);
		}
		
		// FPS counter
		{
			Object * pObject = new Object();
			pObject->m_pTransform	= new Transform();
			pObject->AddComponent( new FpsCounter() );

			scene.AddObject( pObject );
		}
	}

	virtual void Update()
	{
		
	}
};

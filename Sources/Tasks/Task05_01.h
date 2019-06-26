#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Meshes/MeshQuad.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Materials/MaterialSand.h"
#include "GraphicsEngine/Materials/MaterialSand1.h"
#include "GraphicsEngine/Materials/MaterialSand2.h"
#include "GraphicsEngine/Materials/MaterialSand3.h"
#include "GraphicsEngine/Light.h"

#include "Tasks/Task.h"


/**
* @brief Shows how to map a texture to one plane mesh.
* Key code is situated in the classes 
* MaterialSand, MeshQuad, 
* DX11Texture2D, DX11TextureSampler, 
* DX9Texture2D, DX9TextureSampler, 
* GL20Texture2D, GL20TextureSampler.
*/
class Task05_01: public Task
{
public:
	virtual ~Task05_01() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
	
		// Camera
		{
			Object * pCameraObj = new Object();
			Camera * pCamera = new Camera();
			pCameraObj->m_pTransform = new Transform( Vector3(0.0f, 0.5f, -5.0f), Vector3(10.0f, 0.0f, 0.0f) );			
			pCameraObj->AddComponent( pCamera );

			scene.SetCamera( pCamera );
		}

		// Object #1 - Plane with the sand texture (Point filter)
		{
			Object * pObject1 = new Object();

			pObject1->m_pTransform	= new Transform( -0.675,0,0, 0,0,0, 0.35,1,10 );
			pObject1->m_pMesh		= new MeshQuad();
			pObject1->m_pMaterial	= new MaterialSand2(TEXTURE_FILTER_MODE_POINT);
			
			scene.AddObject( pObject1 );
		}

		// Object #2 - Plane with the sand texture (Bilinear filter)
		{
			Object * pObject1 = new Object();

			pObject1->m_pTransform	= new Transform( -0.225,0,0, 0,0,0, 0.35,1,10 );
			pObject1->m_pMesh		= new MeshQuad();			
			pObject1->m_pMaterial	= new MaterialSand2(TEXTURE_FILTER_MODE_BILINEAR);
			
			scene.AddObject( pObject1 );
		}

		// Object #3 - Plane with the sand texture (Trilinear filter)
		{
			Object * pObject1 = new Object();

			pObject1->m_pTransform	= new Transform( 0.225,0,0, 0,0,0, 0.35,1,10 );
			pObject1->m_pMesh		= new MeshQuad();
			pObject1->m_pMaterial	= new MaterialSand2(TEXTURE_FILTER_MODE_TRILINEAR);
			
			scene.AddObject( pObject1 );
		}

		// Object #4 - Plane with the sand texture (Anisotropic filter)
		{
			Object * pObject1 = new Object();

			pObject1->m_pTransform	= new Transform( 0.675,0,0, 0,0,0, 0.35,1,10 );
			pObject1->m_pMesh		= new MeshQuad();
			pObject1->m_pMaterial	= new MaterialSand2(TEXTURE_FILTER_MODE_ANISOTROPIC);
			
			scene.AddObject( pObject1 );
		}
	}

	virtual void Update()
	{
		
	}
};

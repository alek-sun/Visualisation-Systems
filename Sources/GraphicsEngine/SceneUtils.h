#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"


/**
* @brief SceneUtils class provides a list of helper functions.
*/
class SceneUtils
{
public:

	/**
	* @brief Return the world matrix of the object.
	* @param [in] pObject Pointer to the object.
	* @return World matrix that transforms the object position/rotation/scale from the local to the global coordinate system.
	*/
	static const Matrix4x4 GetMatrixWorld(const Object * pObject)
	{
		const Matrix4x4 matWorld = pObject->m_pTransform->GetMatWorld();
		
		return matWorld;
	}

	/**
	* @brief Return the view matrix of the current camera.
	* @return World matrix that transforms the object position/rotation/scale from the global to the camera coordinate system.
	*/
	static const Matrix4x4 GetMatrixView()
	{
		Scene &	scene = Application::Instance().GetScene();
		Camera * pCamera = scene.GetCamera();

		const Matrix4x4 matView = pCamera->GetMatrixView();
		
		return matView;
	}

	/**
	* @brief Return the projection matrix of the current camera.
	* @return Projection matrix that transforms the object position/rotation/scale from the camera to the clip coordinate system.
	*/
	static const Matrix4x4 GetMatrixProj()
	{
		Scene &	scene = Application::Instance().GetScene();
		Camera * pCamera = scene.GetCamera();

		const Matrix4x4 matProj = pCamera->GetMatrixProj();

		return matProj;
	}	

	/**
	* @brief Return the position of the current camera.
	* @return Position of the current camera.
	*/
	static const Vector3 GetEyePosition()
	{
		// TODO: Нужно поставить проверки, что не работает с нулевыми указателями
		Scene &	scene = Application::Instance().GetScene();
		Vector3 eyePos = scene.GetCamera()->GetObjectPtr()->m_pTransform->GetPosition();
		return eyePos;
	}

	/**
	* @brief Return a list of all lights in the scene.
	* @return A list of all lights in the scene.
	*/
	static const std::list<const Light *> GetLights()
	{
		const Scene & scene = Application::Instance().GetScene();
		return scene.GetLights();
	}
};

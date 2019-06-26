#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Matrix4x4.h"
#include "GraphicsEngine/RenderTexture.h"
#include "GraphicsEngine/Ray.h"
#include "GraphicsEngine/Rect.h"
#include "GraphicsEngine/Materials/Material.h"


class Camera : public Component
{
public:
	Camera();

	/**
	* @brief Set background color if render target is the screen.
	* @param [in] r,g,b Background color.
	*/
	void SetBackgroundColor(float r, float g, float b);

	void SetRenderTexture(const RenderTexture * pRenderTexture);
	
	// Установка вертикального угла обзора (в градусах)
	void SetFovY		(float fovY);
	// Установка ближней отсекающей плоскости
	void SetNearPlane	(float nearPlane);
	// Установка дальней отсекающей плоскости
	void SetFarPlane	(float farPlane);

	// Set/Get orthographic mode (true) or perspective mode (false)
	void	SetOrthographic(bool isOrthographic);
	bool	GetOrthographic();

	// Set/Get a half of the vertical size of the viewing volume
	void	SetOrthographicSize(double orthographicSize);
	double	GetOrthographicSize();

	/**
	* @brief Where on the screen is the camera rendered in normalized coordinates
	* http://www.gamedev.net/page/resources/_/technical/game-programming/a-room-with-a-view-r3901.
	*/
	void SetViewport	(Rect rect = Rect(0.0f, 0.0f, 1.0f, 1.0f));
	Rect GetViewport	();
		
	const Matrix4x4 & GetMatrixView();
	const Matrix4x4 & GetMatrixProj();

	/**
	* @brief Returns a ray going from camera through a screen point.
	* @param [in] position Screen point position in pixels (top-left corner is (0,0)).
	*/
	Ray ScreenPointToRay(const Vector3 & position) const;

	/**
	* @brief Transforms position from world space into screen space.
	* @param [in] position Point position in world space.
	*/
	Vector3 WorldToScreenPoint(const Vector3 & position);

	/**
	* @brief Render a scene from position of this camera.
	*/
	void Render(Material * pSpecialMaterial = NULL);

private:

	void RecalculateMatrixProj();
	static void RenderObject( const Object * pObject, Material * pSpecialMaterial );

	// Background color
	float m_r, m_g, m_b;

	// Render texture (if it's NULL then render to the screen, otherwise - to m_pRenderTexture)
	const RenderTexture * m_pRenderTexture;

	// Вертикальный угол обзора в градусах
	float m_fovY;
	float m_nearPlane;
	float m_farPlane;

	// Is the camera orthographic (true) or perspective (false)?
	bool	m_isOrthographic;
	// Camera's half-size when in orthographic mode.
	double	m_orthographicSize;

	Matrix4x4 m_matProj;

	Rect m_viewport;
};

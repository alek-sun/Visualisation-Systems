#include "Camera.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Math.h"
#include "GraphicsEngine/Screen.h"
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Meshes/Mesh.h"

#include "GraphicsEngine/Internal/GraphicsDevice.h"
#include "GraphicsEngine/Internal/InternalGUI.h"
#include "GraphicsEngine/Internal/ObjectStorage.h"


Camera::Camera()
	:	m_r(0.0f), m_g(0.0f), m_b(0.5f),
		m_pRenderTexture(NULL),
		m_fovY(45.0f),
		m_nearPlane(0.01f),
		m_farPlane(1000.0f),
		m_isOrthographic(false),
		m_orthographicSize(10)
{
	
}

void Camera::SetBackgroundColor(float r, float g, float b)
{
	m_r = r;
	m_g = g;
	m_b = b;
}

void Camera::SetRenderTexture(const RenderTexture * pRenderTexture)
{
	m_pRenderTexture = pRenderTexture;
}

// Установка вертикального угла обзора (в градусах)
void Camera::SetFovY( float fovY )
{
	m_fovY = Math::Clamp(fovY, 1.0f, 179.0f);
}

// Установка ближней отсекающей плоскости
void Camera::SetNearPlane( float nearPlane )
{
	//TODO: Добавить проверку на положительность и far > near
	m_nearPlane = nearPlane;
}

// Установка дальней отсекающей плоскости
void Camera::SetFarPlane( float farPlane )
{
	//TODO: Добавить проверку на положительность и far > near
	m_farPlane = farPlane;
}

void Camera::SetOrthographic(bool isOrthographic)
{
	m_isOrthographic = true;
}

bool Camera::GetOrthographic()
{
	return m_isOrthographic;
}

void Camera::SetOrthographicSize(double orthographicSize)
{
	m_orthographicSize = orthographicSize;
}

double Camera::GetOrthographicSize()
{
	return m_orthographicSize;
}

void Camera::SetViewport(Rect rect)
{
	m_viewport = rect;
}

Rect Camera::GetViewport()
{
	return m_viewport;
}

const Matrix4x4 & Camera::GetMatrixView()
{
	return m_pObject->m_pTransform->GetMatView();
}

const Matrix4x4 & Camera::GetMatrixProj()
{
	RecalculateMatrixProj();	

	return m_matProj;
}

Ray Camera::ScreenPointToRay(const Vector3 & position) const
{
	// tg(fovX/2) = (w/2) / zn
	
	// fovX - field of view horizontal
	// w - width of screen in meters
	// zn - near plane in meters

	// (w/2) = zn * tg(fovX/2)
	double wPx = Screen::GetWidth();
	double hPx = Screen::GetHeight();
	double tanFovY2 = tan(DEG2RAD * m_fovY/2);
	double tanFovX2 = tanFovY2 * (wPx/hPx);
	double w2 = m_nearPlane * tanFovX2;
	double h2 = m_nearPlane * tanFovY2;

	// d = zn * forward + (w/2) * (xPx/(wPx/2)) * right + (h/2) * (yPx/(hPx/2)) * up
	// d = normalize(d)
	
	// d - direction, zn - near plane,
	// xPx - mouse x-position in pixels
	// wPx - screen width in pixels
	// yPx - mouse y-position in pixels
	// hPx - screen height in pixels

	Transform * pTrans = this->GetObjectPtr()->m_pTransform;

	Vector3 forward = pTrans->GetForward();
	Vector3 rigth = pTrans->GetRight();
	Vector3 up = pTrans->GetUp();

	double w2Px = wPx * 0.5;
	double h2Px = hPx * 0.5;
	
	double xPx =   position.x - w2Px;
	double yPx = -(position.y - h2Px);

	Vector3 origin = pTrans->GetPosition();
	Vector3 direction = m_nearPlane * forward + w2 * (xPx/w2Px) * rigth + h2 * (yPx/h2Px) * up;
	direction.Normalize();
	
	Ray ray(origin, direction);
	
	// TODO: It will be correct to use in calculation viewport too

	return ray;
}

Vector3 Camera::WorldToScreenPoint(const Vector3 & position)
{
	// Convert to cuboid where x,y,z are in interval [-infinity, infinity]
	Matrix4x4 matViewProj = GetMatrixView() * GetMatrixProj();
	Vector4 result4 = matViewProj * Vector4(position, 1.0);

	// Convert to cuboid where x,y,z are in interval [-1.0, 1.0]
	result4 /= result4.w;
	
	double sw = Screen::GetWidth();
	double sh = Screen::GetHeight();

	// Convert to pixel coordinates
	// where x is in interval [0, screen width]
	// where y is in interval [0, screen height]
	result4.x = ( result4.x + 1.0) * 0.5 * sw;
	result4.y = (-result4.y + 1.0) * 0.5 * sh;

	// TODO: use viewport
	
	Vector3 result(result4.x, result4.y, result4.z);

	return result;
}

void Camera::Render(Material * pSpecialMaterial)
{
	GraphicsEngineImpl * pImpl = NULL;
	{
		GraphicsEngineContext *	pContext = Application::Instance().GetContext();
		pImpl = pContext->m_pImpl;
	}

	// Set render target and viewport
	{
		if (NULL == m_pRenderTexture)
		{
			const int width  = Screen::GetWidth();
			const int height = Screen::GetHeight();

			pImpl->SetRenderTarget(m_r, m_g, m_b);
			pImpl->SetViewport(m_viewport, width, height);
		}
		else
		{
			const int widthPx  = m_pRenderTexture->GetWidth();
			const int heightPx = m_pRenderTexture->GetHeight();

			pImpl->SetRenderTarget(m_pRenderTexture);
			pImpl->SetViewport(m_viewport, widthPx, heightPx);
		}
	}
	
	Scene & scene = Application::Instance().GetScene();
	
	// Render all objects
	ObjectStorage::TraverseAllObjects( &Camera::RenderObject, pSpecialMaterial );
	//{
	//	std::vector<const Object *> objects = scene.GetObjects();

	//	for (size_t i = 0; i < objects.size(); ++i)
	//	{
	//		RenderObject(objects[i], pSpecialMaterial);
	//	}
	//}

	// Render the selected object (in wireframe mode)
	{
		GraphicsDevice::SetFillMode( FILL_MODE_WIREFRAME );

		const Object * pSelectedObject = scene.GetSelectedObject();
		RenderObject(pSelectedObject, pSpecialMaterial);

		GraphicsDevice::SetFillMode( FILL_MODE_SOLID );
	}

	// Render GUI
	InternalGUI::Update();

	// Restore render target
	pImpl->ResetRenderTarget(m_pRenderTexture);
}

void Camera::RecalculateMatrixProj()
{
	double sw = Screen::GetWidth();
	double sh = Screen::GetHeight();

	double vw = m_viewport.w;
	double vh = m_viewport.h;

	double aspect = (sw * vw) / (sh * vh);

	if (m_isOrthographic)
	{
		double h = 2 * m_orthographicSize;
		double w = h * aspect;
		
		m_matProj = Matrix4x4::OrhographicLH( w, h, m_nearPlane, m_farPlane );
	}
	else
	{
		m_matProj = Matrix4x4::PerspectiveFovLH( m_fovY, aspect, m_nearPlane, m_farPlane );
	}
}

void Camera::RenderObject( const Object * pObject, Material * pSpecialMaterial )
{
	if (NULL == pObject || !pObject->IsActive()) return;

	Material *	pMaterial	= (NULL != pSpecialMaterial) ? pSpecialMaterial : pObject->m_pMaterial;
	Mesh *		pMesh		= pObject->m_pMesh;
	if ((NULL == pMaterial) || (NULL == pMesh)) return;
	if (!pMaterial->IsInited()) return;

	pMaterial->SetMaterial(pObject);
	pMesh->Render();
	pMaterial->ResetMaterial();
}

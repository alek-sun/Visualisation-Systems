#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Math.h"
#include "GraphicsEngine/RenderTexture.h"


/**
* @brief Light source type
*/
enum LightType
{
	LIGHT_DIRECTIONAL,
	LIGHT_POINT,
	LIGHT_SPOT,
};

/**
* @brief Light source shadows mode
*/
enum LightShadows
{
	LIGHT_SHADOWS_NONE,	// Do not cast shadows (default)
	LIGHT_SHADOWS_HARD,	// Cast "hard" shadows (with no shadow filtering)
	LIGHT_SHADOWS_SOFT,	// Cast "soft" shadows (with 4x PCF filtering)
};

/**
* @brief Light class is the implementation for the light source.
* Light sources are used for lightning the objects in the scene.
*/
class Light : public Component
{
public:
	Light(LightType type)
		:	m_shadowMode(LIGHT_SHADOWS_NONE),
			m_shadowResolution(1024),
			m_shadowStrength(0.7f),
			m_shadowBias(0.001f),
			m_pShadowMap(NULL)
	{
		switch (type)
		{
			case LIGHT_DIRECTIONAL:
				m_type = 1;
				break;
			case LIGHT_POINT:
				m_type = 2;
				break;
			case LIGHT_SPOT:
				m_type = 3;
				break;
			
			default:
				m_type = 1;
				break;
		}

		m_pShadowMap = new RenderTexture(m_shadowResolution);
	}
	virtual ~Light() {}
	
	virtual Vector4 GetType() const
	{
		return Vector4(m_type,0,0,0);
	}

	virtual Vector4 GetColor() const
	{
		return Vector4(m_color, m_intensity);
	}
	
	virtual Vector3 GetPosition() const
	{
		Vector3 position = m_pObject->m_pTransform->GetPosition();
		return position;
	}

	virtual Vector3 GetDirection() const
	{
		Vector3 direction = m_pObject->m_pTransform->GetForward();
		return direction;
	}

	virtual Vector3 GetEulerAngles() const
	{
		Vector3 eulerAngles = m_pObject->m_pTransform->GetEulerAngles();
		return eulerAngles;
	}

	virtual void SetColor(Vector3 color)
	{
		// Clamp color by interval [0,1]
		m_color = Vector3::Clamp01(color);
	}

	virtual void SetColor(float r, float g, float b)
	{
		// Clamp r, g, b by interval [0,1]
		m_color = Vector3::Clamp01( Vector3(r, g, b) );
	}

	virtual void SetIntensity(float intensity)
	{
		// Clamp intensity by interval [0, +infinity]
		m_intensity = (intensity >= 0) ? intensity : 0;
	}

	/**
	* @brief Set shadow mode (none, hard, soft)
	*/
	void SetShadowMode(const LightShadows & mode)
	{
		m_shadowMode = mode;
	}

	/**
	* @brief Get shadow mode (none, hard, soft)
	*/
	LightShadows GetShadowMode()
	{
		return m_shadowMode;
	}

	/**
	* @brief Set shadow map resolution.
	* @param [in] resolution Shadow map resolution (128, 256, 512, 1024, etc.).
	*/
	void SetShadowResolution(int resolution)
	{
		m_shadowResolution = Math::Clamp(resolution, 128, 2048);
	}

	/**
	* @brief Get shadow map resolution.
	*/
	int GetShadowResolution()
	{
		return m_shadowResolution;
	}

	/**
	* @brief Set shadow strength.
	* @param [in] strength Shadow strength in [0.0, 1.0].
	*/
	void SetShadowStrength(float strength)
	{
		m_shadowStrength = strength;
	}

	/**
	* @brief Get shadow strength.
	* @return Shadow strength in [0.0, 1.0].
	*/
	float GetShadowStrength()
	{
		return m_shadowStrength;
	}

	/**
	* @brief Set shadow bias.
	* @param [in] bias Shadow bias in [0.0, 1.0].
	*/
	void SetShadowBias(float bias)
	{
		m_shadowBias = bias;
	}

	/**
	* @brief Get shadow bias.
	* @return Shadow bias in [0.0, 1.0].
	*/
	float GetShadowBias()
	{
		return m_shadowBias;
	}

	/**
	* @brief Get shadow map.
	* @return Shadow map stored in the render texture.
	*/
	const RenderTexture * GetShadowMap() const
	{
		return m_pShadowMap;
	}

	/**
	* @brief Set matrix that is used for shadows rendering.
	* @param [in] shadowMatViewProj Matrix equal to MatView * MatProj of the camera used for shadows rendering.
	*/
	void SetShadowMatViewProj(const Matrix4x4 & shadowMatViewProj)
	{
		m_shadowMatViewProj = shadowMatViewProj;
	}

	/**
	* @brief Set matrix that is used for shadows rendering.
	* @return Matrix equal to MatView * MatProj of the camera used for shadows rendering.
	*/
	const Matrix4x4 & GetShadowMatViewProj() const
	{
		return m_shadowMatViewProj;
	}
	
protected:
	int				m_type;
	Vector3			m_color;
	float			m_intensity;

	/**
	* @brief Shadows mode (none, hard, soft).
	*/
	LightShadows	m_shadowMode;

	/**
	* @brief Shadows map resolution (128, 256, 512, 1024, etc.).
	*/
	int				m_shadowResolution;

	/**
	* @brief Shadow strength in [0.0, 1.0].
	* 0.0 - transparent shadow
	* 1.0 - black shadow
	*/
	float			m_shadowStrength;

	/**
	* @brief Shadow bias in [0.0, 1.0].
	*/
	float			m_shadowBias;

	/**
	* @brief Shadow map stored in the render texture.
	*/
	RenderTexture * m_pShadowMap;

	Matrix4x4		m_shadowMatViewProj;
	
private:
	Light();
};

#include "Transform.h"
#include <stddef.h>

Transform::Transform()
:	m_pParent			(NULL),
	m_position			(0, 0, 0),
	m_localPosition		(0, 0, 0),
	m_eulerAnglesLocal	(0, 0, 0),
	m_scale				(1, 1, 1)
{
	m_shouldRecalc = true;
}

Transform::Transform(double x, double y, double z)
:	m_pParent			(NULL),
	m_position			(x, y, z),
	m_localPosition		(x, y, z),
	m_eulerAnglesLocal	(0, 0, 0),
	m_scale				(1, 1, 1)
{
	m_shouldRecalc = true;
}

// position (px, py, pz), rotation (rx, ry, rz), scale (sx, sy, sz)
Transform::Transform(double px, double py, double pz, double rx, double ry, double rz, double sx, double sy, double sz)
:	m_pParent			(NULL),
	m_position			(px, py, pz),
	m_localPosition		(px, py, pz),
	m_eulerAnglesLocal	(rx, ry, rz),
	m_scale				(sx, sy, sz)
{
	m_shouldRecalc = true;
}

Transform::Transform(Vector3 position, Vector3 eulerAngles, Vector3 scale)
:	m_pParent			(NULL),
	m_position			(position),
	m_localPosition		(position),
	m_eulerAnglesLocal	(eulerAngles),
	m_scale				(scale)
{
	m_shouldRecalc = true;
}


void Transform::SetParent(Transform * const pParent)
{
	m_pParent = pParent;
	m_shouldRecalc = true;
}

const Vector3 & Transform::GetForward()
{
	if (m_shouldRecalc)
	{
		Recalc();
	}

	return m_forward;
}

const Vector3 & Transform::GetRight()
{
	if (m_shouldRecalc)
	{
		Recalc();
	}

	return m_right;
}

const Vector3 & Transform::GetUp()
{
	if (m_shouldRecalc)
	{
		Recalc();
	}

	return m_up;
}


void Transform::SetLocalPosition( const Vector3 & position )
{
	m_localPosition = position;
	m_shouldRecalc = true;
}

void Transform::SetEulerAngles( const Vector3 & eulerAngles )
{
	// TODO: add code to set local or world
	m_eulerAnglesLocal = eulerAngles;
	m_shouldRecalc = true;
}

void Transform::SetScale( const Vector3 & scale )
{
	m_scale = scale;
	m_shouldRecalc = true;
}

void Transform::Translate( Vector3 vec )
{
	m_localPosition += vec;
	m_shouldRecalc = true;
}


void Transform::Translate( double x, double y, double z )
{
	m_localPosition += Vector3(x, y, z);
	m_shouldRecalc = true;
}


void Transform::Rotate( const Vector3 & euler)
{
	m_eulerAnglesLocal += euler;

	m_shouldRecalc = true;
}

void Transform::Rotate( double x, double y, double z )
{
	Vector3 euler(x,y,z);
	Rotate(euler);
}


const Vector3 & Transform::GetPosition()
{
	if (m_shouldRecalc)
	{
		Recalc();
	}

	return m_position;
}

const Vector3 & Transform::GetEulerAngles() const
{
	// TODO: add code to set local or world
	return m_eulerAnglesLocal;
}

const Vector3 & Transform::GetScale() const
{
	return m_scale;
}

const Vector3 & Transform::GetLocalPosition() const
{
	return m_localPosition;
}

const Matrix4x4 & Transform::GetMatWorld()
{
	//if (m_shouldRecalc)
	{
		Recalc();
	}

	return m_matWorld;
}

const Matrix4x4 & Transform::GetMatView()
{
	//if (m_shouldRecalc)
	{
		Recalc();
	}

	return m_matView;
}

void Transform::Recalc()
{
	// ѕересчитаем матрицу World
	{
		Matrix4x4 matTrans		= Matrix4x4::Translation(m_localPosition);
		Matrix4x4 matRotLocal	= Matrix4x4::Rotation(m_eulerAnglesLocal);
		Matrix4x4 matScale		= Matrix4x4::Scaling(m_scale);

		m_matWorld = matScale * matRotLocal * matTrans;
		
		// If has parent then use parent matrix
		if (NULL != m_pParent)
		{
			Matrix4x4 matWorldParent = m_pParent->GetMatWorld();
			m_matWorld = m_matWorld * matWorldParent;
		}

		// Calculate position in the global coordinate system
		Vector4 position4 = m_matWorld * Vector4(0, 0, 0, 1);
		m_position = Vector3(position4.x, position4.y, position4.z);
	}

	// ѕересчитаем вектора m_forward, m_right, m_up
	{
		Vector4 forward4 = m_matWorld * Vector4(0, 0, 1, 0);
		m_forward = forward4.ToVector3();
		m_forward.Normalize();

		Vector4 right4 = m_matWorld * Vector4(1, 0, 0, 0);
		m_right = right4.ToVector3();
		m_right.Normalize();

		Vector4 up4 = m_matWorld * Vector4(0, 1, 0, 0);
		m_up = up4.ToVector3();
		m_up.Normalize();
	}

	// ѕересчитываем матрицу View
	{
		m_matView = Matrix4x4::LookAtLH(m_position, m_position + m_forward, m_up);
	}

	m_shouldRecalc = false;
}

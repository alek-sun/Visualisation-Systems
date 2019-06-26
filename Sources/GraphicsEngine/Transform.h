#pragma once
#include "GraphicsEngine/Vector3.h"
#include "GraphicsEngine/Matrix4x4.h"

class Transform
{
public:
	Transform();
	// TODO: Заменить float на double
	Transform(double x, double y, double z);
	// position (px, py, pz), rotation (rx, ry, rz), scale (sx, sy, sz)
	Transform(double px, double py, double pz, double rx, double ry, double rz, double sx, double sy, double sz);
	Transform(Vector3 position, Vector3 eulerAngles = Vector3(0,0,0), Vector3 scale = Vector3(1,1,1));
	
	/*
	* @brief Set parent object.
	* Position, rotation and scale will be relative to the parent.
	*/
	void SetParent(Transform * const pParent);

	const Vector3 & GetForward();
	const Vector3 & GetRight();
	const Vector3 & GetUp();

	/*
	* @brief Set the object position in the local coordinate system (relatively to the parent).
	* @param [in] position The local position vector.
	*/
	void SetLocalPosition(const Vector3 & position);
	void SetEulerAngles	(const Vector3 & eulerAngles);
	void SetScale		(const Vector3 & scale);

	/*
	* @brief Translates the object in the local coordinate system.
	* @param [in] vec The translation vector.
	*/
	void Translate		(Vector3 vec);

	/*
	* @brief Translates the object in the local coordinate system.
	* @param [in] x,y,z The translation vector.
	*/
	void Translate		(double x, double y, double z);

	/*
	* @brief Rotate object in local or world coordinate system.
	*/
	void Rotate			(const Vector3 & euler);

	/*
	* @brief Rotate object in local or world coordinate system.
	*/
	void Rotate			(double x, double y, double z);

	/*
	* @brief Returns the object position in the global coordinate system.
	*/
	const Vector3 & GetPosition();
	
	const Vector3 & GetEulerAngles() const;
	const Vector3 & GetScale() const;

	/*
	* @brief Returns the object position in the locat coordinate system (relatively to the parent).
	*/
	const Vector3 & GetLocalPosition() const;

	const Matrix4x4 & GetMatWorld();
	const Matrix4x4 & GetMatView();

private:

	void Recalc();

	Transform * m_pParent;

	Vector3 m_position;
	Vector3 m_localPosition;
	Vector3 m_eulerAnglesLocal;
	Vector3 m_scale;

	// Вектор "вперёд" в глобальной с.к. (равен (0,0,1) в локальной с.к.)
	Vector3 m_forward;
	// Вектор "вправо" в глобальной с.к. (равен (1,0,0) в локальной с.к.)
	Vector3 m_right;
	// Вектор "вверх" в глобальной с.к. (равен (0,1,0) в локальной с.к.)
	Vector3 m_up;

	Matrix4x4 m_matWorld;
	Matrix4x4 m_matView;

	bool m_shouldRecalc;
};

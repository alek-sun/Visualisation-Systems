#pragma once
#include "GraphicsEngine/Matrix4x4.h"

/**
* @brief MathUtils class provides a list of helper functions.
*/
class MathUtils
{
public:
	
	/**
	* @brief Return the world view projection matrix by calculating using the rules of the graphics engine.
	* @param [in] matWorld World matrix.
	* @param [in] matView View matrix.
	* @param [in] matProj Projection matrix.
	* @return World view projection matrix.
	*/
	static const Matrix4x4 GetMatrixWorldViewProjT(const Matrix4x4 & matWorld, const Matrix4x4 & matView, const Matrix4x4 & matProj)
	{
		const Matrix4x4 & matWorldViewProj = matWorld * matView * matProj;

		const Matrix4x4 & matWorldViewProjT = matWorldViewProj.Transpose();

		return matWorldViewProjT;
	}

	/**
	* @brief Return the world view projection matrix by calculating using the rules of the graphics engine.
	* @param [in] matWorld World matrix.
	* @param [in] matViewProj View projection matrix.
	* @return World view projection matrix.
	*/
	static const Matrix4x4 GetMatrixWorldViewProjT(const Matrix4x4 & matWorld, const Matrix4x4 & matViewProj)
	{
		const Matrix4x4 & matWorldViewProj = matWorld * matViewProj;

		const Matrix4x4 & matWorldViewProjT = matWorldViewProj.Transpose();

		return matWorldViewProjT;
	}

	/**
	* @brief Return the view projection matrix by calculating using the rules of the graphics engine.
	* @param [in] matView View matrix.
	* @param [in] matProj Projection matrix.
	* @return View projection matrix.
	*/
	static const Matrix4x4 GetMatrixViewProj(const Matrix4x4 & matView, const Matrix4x4 & matProj)
	{
		const Matrix4x4 & matViewProj = matView * matProj;

		return matViewProj;
	}

	/**
	* @brief Return the transposed matrix by calculating using the rules of the graphics engine.
	* @param [in] mat Matrix to transpose.
	* @return Transposed matrix.
	*/
	static const Matrix4x4 GetMatrixTranspose(const Matrix4x4 & mat)
	{
		const Matrix4x4 & matT = mat.Transpose();	
		
		return matT;
	}

	/**
	* @brief Return the inversed matrix by calculating using the rules of the graphics engine.
	* @param [in] mat Matrix to inverse.
	* @return Inversed matrix.
	*/
	static const Matrix4x4 GetMatrixInverse(const Matrix4x4 & mat)
	{
		const Matrix4x4 & matInverse = mat.Inverse();
		
		return matInverse;
	}
};

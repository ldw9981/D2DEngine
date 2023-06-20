#include "pch.h"
#include "RendererHelper.h"

void GetRotationFromMatrix(const D2D_MATRIX_3X2_F& mat, float& Rotation)
{
	Rotation = atan2f(mat._21, mat._11);
}

void GetScaleFromMatrix(const D2D_MATRIX_3X2_F& mat, float& ScaleX, float& ScaleY)
{
	ScaleX = sqrtf(mat._11 * mat._11 + mat._12 * mat._12);
	ScaleY = sqrtf(mat._21 * mat._21 + mat._22 * mat._22);
}

void GetPositionFromMatrix(const D2D_MATRIX_3X2_F& mat, float& x, float& y)
{
	x = mat._31;
	y = mat._32;
}

void SetRotationToMatrix(D2D_MATRIX_3X2_F& mat, float Rotation)
{
	mat._11 = cosf(Rotation);
	mat._12 = sinf(Rotation);
	mat._21 = -sinf(Rotation);
	mat._22 = cosf(Rotation);
}

void SetScaleToMatrix(D2D_MATRIX_3X2_F& mat, float ScaleX, float ScaleY)
{
	mat._11 = ScaleX;
	mat._22 = ScaleY;
}

void SetPositionToMatrix(D2D_MATRIX_3X2_F& mat, float x, float y)
{
	mat._31 = x;
	mat._32 = y;
}
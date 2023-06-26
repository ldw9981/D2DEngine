#include "pch.h"
#include "RendererHelper.h"

void GetRotationFromMatrix(const D2D_MATRIX_3X2_F& mat, float* Rotation)
{
	*Rotation = atan2f(mat._21, mat._11);
}

void GetScaleFromMatrix(const D2D_MATRIX_3X2_F& mat, float* ScaleX, float* ScaleY)
{
	*ScaleX = sqrtf(mat._11 * mat._11 + mat._12 * mat._12);
	*ScaleY = sqrtf(mat._21 * mat._21 + mat._22 * mat._22);
}

void GetLocationFromMatrix(const D2D_MATRIX_3X2_F& mat, float* x, float* y)
{
	*x = mat._31;
	*y = mat._32;
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

/*
	회전에 문제가 생겨 사용안함
*/
void ModifyMatrixtForBottomUpScreenSpace(ID2D1RenderTarget* pRenderTarget, D2D_MATRIX_3X2_F& in_out)
{
	//in_out._32 = pRenderTarget->GetSize().height - in_out._32;
}

bool CheckCollision(const D2D_RECT_F& rc1, const D2D_RECT_F& rc2)
{
	if (rc1.left < rc2.right && rc1.right > rc2.left &&
		rc1.top < rc2.bottom && rc1.bottom > rc2.top)
	{
		return true;
	}
	return false;
}

bool CheckPointCollision(const D2D_RECT_F& rc, const D2D_POINT_2F& pt)
{
	if (rc.left < pt.x && rc.right > pt.x &&
		rc.top < pt.y && rc.bottom > pt.y)
	{
		return true;
	}
	return false;
}


void SetPositionToMatrix(D2D_MATRIX_3X2_F& mat, float x, float y)
{
	mat._31 = x;
	mat._32 = y;
}

// minX : rc.left
// maxX : rc.right

// maxY : rc.top
// minY : rc.bottom
bool IntersectSphereAndRect(const D2D_RECT_F& rc, const D2D_POINT_2F& center, float radius)
{
	// get the closest point to the circle within the rectangle

	float x = fmaxf(rc.left, fminf(center.x, rc.right));
	float y = fmaxf(rc.bottom, fminf(center.y, rc.top));
	
	float dx = x - center.x;
	float dy = y - center.y;

	float dist = sqrtf(dx * dx + dy * dy);

	if (dist <= radius)
		return true;

	return false;
}
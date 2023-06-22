#pragma once
/*
	Render에서 유용한 매크로나 함수를 정의한다.
*/

template <typename T>
void SAFE_RELEASE(T* p)
{
	if (p)
	{
		p->Release();
		p = nullptr;
	}
}

template <typename T>
void SAFE_DELETE(T* p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

void GetRotationFromMatrix(const D2D_MATRIX_3X2_F& mat, float& Rotation);
void GetScaleFromMatrix(const D2D_MATRIX_3X2_F& mat, float& ScaleX, float& ScaleY);
void GetPositionFromMatrix(const D2D_MATRIX_3X2_F& mat, float& x, float& y);
void SetRotationToMatrix(D2D_MATRIX_3X2_F& mat, float Rotation);
void SetScaleToMatrix(D2D_MATRIX_3X2_F& mat, float ScaleX, float ScaleY);


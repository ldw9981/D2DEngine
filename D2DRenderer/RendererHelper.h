#pragma once
/*
	Render���� ������ ��ũ�γ� �Լ��� �����Ѵ�.
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




void GetRotationFromMatrix(const D2D_MATRIX_3X2_F& mat, float* Rotation);
void GetScaleFromMatrix(const D2D_MATRIX_3X2_F& mat, float* ScaleX, float* ScaleY);
void GetLocationFromMatrix(const D2D_MATRIX_3X2_F& mat, float* x, float* y);
void SetRotationToMatrix(D2D_MATRIX_3X2_F& mat, float Rotation);
void SetScaleToMatrix(D2D_MATRIX_3X2_F& mat, float ScaleX, float ScaleY);

// ȭ���ϴ��� 0,0 �� ��ǥ��� ��ȯ�Ѵ�.
void ModifyMatrixtForBottomUpScreenSpace(ID2D1RenderTarget* pRenderTarget,D2D_MATRIX_3X2_F& in_out);	


bool CheckCollision(const D2D_RECT_F& rc1, const D2D_RECT_F& rc2);

bool IntetsectSphereAndRect(const D2D_RECT_F& rc, const D2D_POINT_2F& center, float radius);
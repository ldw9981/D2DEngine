#pragma once



void GetRotationFromMatrix(const D2D_MATRIX_3X2_F& mat, float& Rotation);
void GetScaleFromMatrix(const D2D_MATRIX_3X2_F& mat, float& ScaleX, float& ScaleY);
void GetPositionFromMatrix(const D2D_MATRIX_3X2_F& mat, float& x, float& y);
void SetRotationToMatrix(D2D_MATRIX_3X2_F& mat, float Rotation);
void SetScaleToMatrix(D2D_MATRIX_3X2_F& mat, float ScaleX, float ScaleY);


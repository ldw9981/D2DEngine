#pragma once
/**
	@file      SimpleMathHelper.h
	@brief     벡터 연산을 위한 간단한 수학 연산을 위한 헤더 파일입니다.
	@author    SKYFISH
	@date      JUNE.2023
	@notice    52반 수업을 위한 테스트용 코드이며 수정 중에 있습니다.
**/


#pragma once

#include <D2D1Helper.h>
#include <math.h>
#include <vector>

namespace mathHelper
{
	//
	// DX 에 정의된 구조체를 상속받아 연산자 재정의 추가
	// 
	class Vector2F : public D2D_VECTOR_2F
	{
	public:
		Vector2F() = default;

		Vector2F(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2F(const D2D_VECTOR_2F& vector)
		{
			this->x = vector.x;
			this->y = vector.y;
		}

		Vector2F(const Vector2F&) = default;

		Vector2F& operator=(const Vector2F&) = default;

		Vector2F(Vector2F&&) = default;

		Vector2F& operator=(Vector2F&&) = default;

		~Vector2F() = default;

		Vector2F operator+(const Vector2F& vector) const
		{
			return Vector2F(this->x + vector.x, this->y + vector.y);
		}

		Vector2F operator-(const Vector2F& vector) const
		{
			return Vector2F(this->x - vector.x, this->y - vector.y);
		}

		Vector2F operator*(float scalar) const
		{
			return Vector2F(this->x * scalar, this->y * scalar);
		}

		Vector2F operator/(float scalar) const
		{
			return Vector2F(this->x / scalar, this->y / scalar);
		}

		Vector2F& operator+=(const Vector2F& vector)
		{
			this->x += vector.x;
			this->y += vector.y;

			return *this;
		}

		Vector2F& operator-=(const Vector2F& vector)
		{
			this->x -= vector.x;
			this->y -= vector.y;
			return *this;
		}

		Vector2F& operator*=(float scalar)
		{
			this->x *= scalar;
			this->y *= scalar;
			return *this;
		}

		Vector2F& operator/=(float scalar)
		{
			this->x /= scalar;
			this->y /= scalar;
			return *this;
		}

		bool operator==(const Vector2F& vector) const
		{
			return (this->x == vector.x && this->y == vector.y);
		}

		float Length() const
		{
			return sqrtf(this->x * this->x + this->y * this->y);
		}

		float LengthSquared() const
		{
			return (this->x * this->x + this->y * this->y);
		}

		float Normalize()
		{
			float length = Length();

			if (length > 0.0f)
			{
				float invLength = 1.0f / length;
				this->x *= invLength;
				this->y *= invLength;
			}

			return length;
		}

	};

	//
	// DX 에 정의된 구조체를 상속받아 연산자 재정의 추가
	// 
	class Vector3F : public D2D_VECTOR_3F
	{
	public:
		Vector3F() = default;

		Vector3F(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}
		Vector3F(const D2D_VECTOR_3F& vector)
		{
			this->x = vector.x;
			this->y = vector.y;
			this->z = vector.z;
		}

		Vector3F(const Vector3F&) = default;

		Vector3F& operator=(const Vector3F&) = default;

		Vector3F(Vector3F&&) = default;

		Vector3F& operator=(Vector3F&&) = default;

		~Vector3F() = default;

		Vector3F operator+(const Vector3F& vector) const
		{
			return Vector3F(this->x + vector.x, this->y + vector.y, this->z + vector.z);
		}

		Vector3F operator-(const Vector3F& vector) const
		{
			return Vector3F(this->x - vector.x, this->y - vector.y, this->z - vector.z);
		}

		Vector3F operator*(float scalar) const
		{
			return Vector3F(this->x * scalar, this->y * scalar, this->z * scalar);
		}

		Vector3F operator/(float scalar) const
		{
			return Vector3F(this->x / scalar, this->y / scalar, this->z / scalar);
		}

		Vector3F& operator+=(const Vector3F& vector)
		{
			this->x += vector.x;
			this->y += vector.y;
			this->z += vector.z;
			return *this;
		}

		Vector3F& operator-=(const Vector3F& vector)
		{
			this->x -= vector.x;
			this->y -= vector.y;
			this->z -= vector.z;
			return *this;
		}

		Vector3F& operator*=(float scalar)
		{
			this->x *= scalar;
			this->y *= scalar;
			this->z *= scalar;
			return *this;
		}
		Vector3F& operator/=(float scalar)
		{
			this->x /= scalar;
			this->y /= scalar;
			this->z /= scalar;
			return *this;
		}

		bool operator==(const Vector3F& vector) const
		{
			return (this->x == vector.x && this->y == vector.y && this->z == vector.z);
		}

		float Length() const
		{
			return sqrtf(this->x * this->x + this->y * this->y + this->z * this->z);
		}

		float LengthSquared() const
		{
			return (this->x * this->x + this->y * this->y + this->z * this->z);
		}

		float Normalize()
		{
			float length = Length();

			if (length > 0.0f)
			{
				float invLength = 1.0f / length;
				this->x *= invLength;
				this->y *= invLength;
				this->z *= invLength;
			}
			return length;
		}

	};
}

#pragma once
#include<assert.h>
class Vec2
{
public:
	Vec2();
	~Vec2();
	Vec2(float _x, float _y);
	Vec2(int _x, int _y);
	Vec2(POINT _pt);
	Vec2(const Vec2& _vec);

public:
	bool IsZero() { return x == 0 && y == 0; }
	float Length() { return (float)(sqrt(pow(x, 2) + pow(y, 2))); }

	Vec2& Normalize()
	{
		float fLen = Length();
		// 0�̸� �ȵ�.
		assert(fLen !=0.f);
		x /= fLen;
		y /= fLen;
		return *this;
	}
	Vec2 operator + (Vec2 _vOther)
	{
		return Vec2(x + _vOther.x, y + _vOther.y);
	}
	Vec2 operator - (Vec2 _vOther)
	{
		return Vec2(x - _vOther.x, y - _vOther.y);
	}
	Vec2 operator * (Vec2 _vOther)
	{
		return Vec2(x * _vOther.x, y * _vOther.y);
	}
	Vec2 operator / (Vec2 _vOther)
	{
		assert(!(0.f == _vOther.x || 0.f == _vOther.y));
		return Vec2(x / _vOther.x, y / _vOther.y);
	}
	Vec2 operator / (float _vOther)
	{
		assert(!(0.f == _vOther || 0.f == _vOther));
		return Vec2(x / _vOther, y / _vOther);
	}
	Vec2 operator * (float _vOther)
	{
		//assert(!(0.f == _vOther || 0.f == _vOther));
		return Vec2(x * _vOther, y * _vOther);
	}
	Vec2 operator * (int _i)
	{
		return Vec2(x * (float)_i, y * (float)_i);
	}
	Vec2& operator += (const Vec2& _vOther)
	{
		(*this) = (*this) + _vOther;
		return *this;
	}
	Vec2& operator -= (const Vec2& _vOther)
	{
		(*this) = (*this) - _vOther;
		return *this;
	}Vec2& operator *= (const Vec2& _vOther)
	{
		(*this) = (*this) * _vOther;
		return *this;
	}Vec2& operator /= (const Vec2& _vOther)
	{
		(*this) = (*this) / _vOther;
		return *this;
	}
	Vec2& operator=(const Vec2& _vOther)
	{
		x = _vOther.x;
		y = _vOther.y;
		return *this;
	}
public:
	float x;
	float y;
};


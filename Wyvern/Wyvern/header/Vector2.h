// Vector2.h

#ifndef __VECTOR2__
#define __VECTOR2__

struct Vector2
{
	float x_, y_;

	Vector2();
	Vector2(const Vector2& rhs);
	Vector2(const float x, const float y);
	Vector2(const int x, const int y);
	Vector2(const float x, const int y);
	Vector2(const int x, const float y);
	Vector2& operator=(const Vector2& rhs);
	Vector2 operator-() const;
	Vector2 operator+(const Vector2& rhs) const;
	Vector2 operator-(const Vector2& rhs) const;
	Vector2 operator*(const Vector2& rhs) const;
	Vector2 operator*(const float rhs) const;
	Vector2 operator/(const Vector2& rhs) const;
	Vector2 operator/(const float rhs) const;

	friend Vector2 operator+=(Vector2 lhs, const Vector2& rhs);
	friend Vector2 operator-=(Vector2 lhs, const Vector2& rhs);
	friend Vector2 operator*=(Vector2 lhs, const Vector2& rhs);
	friend Vector2 operator*=(Vector2 lhs, const float rhs);
	friend Vector2 operator/=(Vector2 lhs, const Vector2& rhs);
	friend Vector2 operator/=(Vector2 lhs, const float rhs);

	float Length_Sqrt() const;
	float Length() const;
	void Normalise() const;
	Vector2 Unit() const;
	float Dot(const Vector2& rhs) const;
	float Cross(const Vector2& rhs) const;
	float Distance(const Vector2& rhs) const;
	
};


#endif // !__VECTOR2__
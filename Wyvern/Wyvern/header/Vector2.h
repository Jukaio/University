// Vector2.h

#ifndef __VECTOR2__
#define __VECTOR2__

//https://gist.github.com/leegrey/1020522/3a39c1b65c8ed2e48107b971b159a56324823aee

struct Vector2
{
	float x_, y_;

	Vector2 As_Grid();

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
	Vector2 operator/(const Vector2& rhs) const;
	Vector2 operator/(const float rhs) const;
	Vector2 operator*(const float rhs) const;
	Vector2 operator/(const int rhs) const;
	Vector2 operator*(const int rhs) const;

	friend Vector2& operator+=(Vector2& lhs, const Vector2& rhs);
	friend Vector2& operator-=(Vector2& lhs, const Vector2& rhs);
	friend Vector2& operator*=(Vector2& lhs, const Vector2& rhs);
	friend Vector2& operator*=(Vector2& lhs, const float rhs);
	friend Vector2& operator/=(Vector2& lhs, const Vector2& rhs);
	friend Vector2& operator/=(Vector2& lhs, const float rhs);
	friend bool operator==(const Vector2& lhs, const Vector2& rhs);

	float Length_Sqrt() const;
	float Length() const;
	void Normalise();
	Vector2 Unit() const;
	float Dot(const Vector2& rhs) const;
	float Cross(const Vector2& rhs) const;
	float Distance_To(const Vector2& rhs) const;


	
};

#endif // !__VECTOR2__
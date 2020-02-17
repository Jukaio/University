// Vector2.cpp

#include "Vector2.h"
#include <math.h>

Vector2::Vector2()
	: x_(0)
	, y_(0)
{

}

Vector2::Vector2(const Vector2& rhs)
	: x_(rhs.x_)
	, y_(rhs.y_)
{

}

Vector2::Vector2(const float x, const float y)
	: x_(x)
	, y_(y)
{

}

Vector2::Vector2(const int x, const int y)
	: x_((float) x)
	, y_((float) y)
{
}

Vector2::Vector2(const float x, const int y)
	: x_(x)
	, y_((float) y)
{
}

Vector2::Vector2(const int x, const float y)
	: x_((float) x)
	, y_(y)
{
}

Vector2& Vector2::operator=(const Vector2& rhs)
{
	x_ = rhs.x_;
	y_ = rhs.y_;

	return *this;
}

Vector2 Vector2::operator-() const
{
	return Vector2(-x_, -y_);
}

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(x_ + rhs.x_, y_ + rhs.y_);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(x_ - rhs.x_, y_ - rhs.y_);
}

Vector2 Vector2::operator*(const Vector2& rhs) const
{
	return Vector2(x_ * rhs.x_, y_ * rhs.y_);
}

Vector2 Vector2::operator*(const float rhs) const
{
	return Vector2(x_ * rhs, y_ * rhs);
}

Vector2 Vector2::operator/(const int rhs) const
{
	return Vector2(x_ / (float) rhs, y_ / (float) rhs);;
}

Vector2 Vector2::operator*(const int rhs) const
{
	return Vector2(x_ * rhs, y_ * rhs);;
}

Vector2 Vector2::operator/(const Vector2& rhs) const
{
	return Vector2(x_ / rhs.x_, y_ / rhs.y_);
}

Vector2 Vector2::operator/(const float rhs) const
{
	return Vector2(x_ / rhs, y_ / rhs);
}

//Friend Mehtods
Vector2& operator+=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x_ += rhs.x_;
	lhs.y_ += rhs.y_;

	return lhs;
}

Vector2& operator-=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x_ -= rhs.x_;
	lhs.y_ -= rhs.y_;

	return lhs;
}

Vector2& operator*=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x_ *= rhs.x_;
	lhs.y_ *= rhs.y_;

	return lhs;
}

Vector2& operator*=(Vector2& lhs, const float rhs)
{
	lhs.x_ *= rhs;
	lhs.y_ *= rhs;

	return lhs;
}

Vector2& operator/=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x_ /= rhs.x_;
	lhs.y_ /= rhs.y_;

	return lhs;
}

Vector2& operator/=(Vector2& lhs, const float rhs)
{
	lhs.x_ /= rhs;
	lhs.y_ /= rhs;

	return lhs;
}


float Vector2::Length_Sqrt() const
{
	return x_ * x_ + y_ * y_;
}

float Vector2::Length() const
{
	return sqrtf(Length_Sqrt());
}

void Vector2::Normalise()
{
	float l = Length();
	if (l > 0.0f)
	{
		x_ /= l;
		y_ /= l;
	}
}

Vector2 Vector2::Unit() const
{
	Vector2 result(*this);
	result.Normalise();
	return result;
}

float Vector2::Dot(const Vector2& rhs) const
{
	return x_ * rhs.x_ + y_ * rhs.y_;
}

float Vector2::Cross(const Vector2& rhs) const
{
	return x_ * rhs.y_ - y_ * rhs.x_;
}

float Vector2::Distance_To(const Vector2& rhs) const
{
	return sqrtf(powf((rhs.x_ - x_), 2) + powf((rhs.y_ - y_), 2));
}

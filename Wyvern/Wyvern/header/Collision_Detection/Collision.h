// Collision.h

#ifndef __COLLISION__
#define __COLLISION__

#include "Collider.h"


bool Collision(const Vector2& point_A, const Vector2& point_B)
{
	if (point_A.x_ == point_B.x_ && point_A.y_ == point_B.y_)
		return true;
	return false;
}

bool Collision(const Circle& circle, const Vector2& point)
{
	float distance = circle.position_.Distance_To(point);

	if (distance <= circle.radius_)
		return true;
	return false;
}

bool Collision(const Vector2& point, const Circle& circle)
{
	return Collision(circle, point);
}

bool Collision(const Circle& circle_A, const Circle& circle_B)
{
	float distance = circle_A.position_.Distance_To(circle_B.position_);

	if (distance <= circle_A.radius_ + circle_B.radius_)
		return true;
	return false;
}

bool Collision(const Vector2& point, const Rectangle& rect)
{
	return (point.x_ >= rect.position_.x_ &&
			point.x_ <= rect.position_.x_ + rect.size_.x_ &&
			point.y_ >= rect.position_.y_ &&
			point.y_ <= rect.position_.y_ + rect.size_.y_);
}

bool Collision(const Rectangle& rect, const Vector2& point)
{
	return Collision(point, rect);
}

bool Collision(const Circle& circle, const Rectangle& rect)
{
	Vector2 test = circle.position_;

	if (circle.position_.x_ < rect.position_.x_)						test.x_ = rect.position_.x_;
	else if (circle.position_.x_ > rect.position_.x_ + rect.size_.x_)	test.x_ = rect.position_.x_ + rect.size_.x_;
	if (circle.position_.y_ < rect.position_.y_)						test.y_ = rect.position_.y_;
	else if (circle.position_.y_ > rect.position_.y_ + rect.size_.y_)	test.y_ = rect.position_.y_ + rect.size_.y_;

	float distance = test.Distance_To(circle.position_);

	if (distance <= circle.radius_)
		return true;
	return false;
}

bool Collision(const Rectangle& rect, const Circle& circle)
{
	return Collision(circle, rect);
}

bool Collision(const Rectangle& rect_A, const Rectangle& rect_B)
{
	return (rect_A.position_.x_ + rect_A.size_.x_ >= rect_B.position_.x_ &&
			rect_A.position_.x_ <= rect_B.position_.x_ + rect_B.size_.x_ &&
			rect_A.position_.y_ + rect_A.size_.y_ >= rect_B.position_.y_ &&
			rect_A.position_.y_ <= rect_B.position_.y_ + rect_B.size_.y_);
}



#endif // !__COLLISION__

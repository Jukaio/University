// Collision.h

#ifndef __COLLISION__
#define __COLLISION__

#include "Collider.h"

// Line collision missing :(( 

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
	float rect_Right = rect.position_.x_ + rect.size_.x_ - (rect.origin_.x_ * rect.size_.x_);
	float rect_Left = rect.position_.x_ - (rect.origin_.x_ * rect.size_.x_);
	float rect_Top = rect.position_.y_ - (rect.origin_.y_ * rect.size_.y_);
	float rect_Bottom = rect.position_.y_ + rect.size_.y_ - (rect.origin_.y_ * rect.size_.y_);

	return (point.x_ >= rect_Left &&
			point.x_ <= rect_Right &&
			point.y_ >= rect_Top &&
			point.y_ <= rect_Bottom);
}

bool Collision(const Rectangle& rect, const Vector2& point)
{
	return Collision(point, rect);
}

bool Collision(const Circle& circle, const Rectangle& rect)
{
	float rect_Right = rect.position_.x_ + rect.size_.x_ - (rect.origin_.x_ * rect.size_.x_);
	float rect_Left = rect.position_.x_ - (rect.origin_.x_ * rect.size_.x_);
	float rect_Top = rect.position_.y_ - (rect.origin_.y_ * rect.size_.y_);
	float rect_Bottom = rect.position_.y_ + rect.size_.y_ - (rect.origin_.y_ * rect.size_.y_);

	Vector2 test = circle.position_;

	if (circle.position_.x_ < rect_Left)			test.x_ = rect.position_.x_;
	else if (circle.position_.x_ > rect_Right)		test.x_ = rect.position_.x_ + rect.size_.x_;
	if (circle.position_.y_ < rect_Top)				test.y_ = rect.position_.y_;
	else if (circle.position_.y_ > rect_Bottom)		test.y_ = rect.position_.y_ + rect.size_.y_;

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
	float rect_A_Right = rect_A.position_.x_ + rect_A.size_.x_ - (rect_A.origin_.x_ * rect_A.size_.x_);
	float rect_A_Left = rect_A.position_.x_ - (rect_A.origin_.x_ * rect_A.size_.x_);
	float rect_A_Top = rect_A.position_.y_ - (rect_A.origin_.y_ * rect_A.size_.y_);
	float rect_A_Bottom = rect_A.position_.y_ + rect_A.size_.y_ - (rect_A.origin_.y_ * rect_A.size_.y_);

	float rect_B_Right = rect_B.position_.x_ + rect_B.size_.x_ - (rect_B.origin_.x_ * rect_B.size_.x_);
	float rect_B_Left = rect_B.position_.x_ - (rect_B.origin_.x_ * rect_B.size_.x_);
	float rect_B_Top = rect_B.position_.y_ - (rect_B.origin_.y_ * rect_B.size_.y_);
	float rect_B_Bottom = rect_B.position_.y_ + rect_B.size_.y_ - (rect_B.origin_.y_ * rect_B.size_.y_);

	return (rect_A_Right >= rect_B_Left &&
			rect_A_Left <= rect_B_Right &&
			rect_A_Bottom >= rect_B_Top &&
			rect_A_Top <= rect_B_Bottom);
}



#endif // !__COLLISION__

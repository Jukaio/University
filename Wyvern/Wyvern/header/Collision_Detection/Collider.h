// Collider.h

#ifndef __COLLIDER__
#define __COLLIDER__

#include "Vector2.h"

struct Circle
{
	Vector2 position_;
	float radius_;
	Circle() : position_(0, 0), radius_(0.0f) { }
	Circle(Vector2 position, float radius) : position_(position), radius_(radius) { }
	Circle(int x, int y, float radius) : position_(x, y), radius_(radius) { }
	Circle(float x, float y, float radius) : position_(x, y), radius_(radius) { }
};

struct Line
{
	Vector2 start_;
	Vector2 end_;

	Line() : start_(0, 0), end_(0, 0) { }
	Line(Vector2 start, Vector2 end) : start_(start), end_(end) { }
	Line(int start_x, int start_y, int end_x, int end_y) : start_(start_x, start_y), end_(end_x, end_y) { }
	Line(float start_x, float start_y, float end_x, float end_y) : start_(start_x, start_y), end_(end_x, end_y) { }
};

struct Rectangle
{
	Vector2 position_;
	Vector2 origin_;
	Vector2 size_;

	Rectangle() : position_(0, 0), size_(0, 0), origin_(0, 0) { }
	Rectangle(Vector2 position, Vector2 size, Vector2 origin = Vector2(0, 0)) : position_(position), size_(size), origin_(origin) { }
	Rectangle(int x, int y, int w, int h, int origin_x = 0, int origin_y = 0) : position_(x, y), size_(w, h), origin_(origin_x, origin_y) { }
	Rectangle(float x, float y, float w, float h, float origin_x = 0.0f, float origin_y = 0.0f) : position_(x, y), size_(w, h), origin_(origin_x, origin_y) { }
};




#endif // !__COLLIDER__

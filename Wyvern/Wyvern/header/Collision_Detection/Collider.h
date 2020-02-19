// Collider.h

#ifndef __COLLIDER__
#define __COLLIDER__

#include "Vector2.h"
#include "Entity.h"


struct Collider
{
	Entity* parent_ = nullptr;
	Vector2 position_;

	void Set_Parent(Entity* parent)
	{
		parent_ = parent;
	}
	void Update_Position(Vector2 position)
	{
		position_ = position;
	}

	Collider() { }
	Collider(Vector2 positiom) : position_(positiom) { }
};

struct Circle : Collider
{
	float radius_;
	Circle() : Collider(Vector2(0,0)), radius_(0.0f) { }
	Circle(Vector2 position, float radius) : Collider(position), radius_(radius) { }
	Circle(int x, int y, float radius) : Collider(Vector2(x, y)), radius_(radius) { }
	Circle(float x, float y, float radius) : Collider(Vector2(x, y)), radius_(radius) { }
};

struct Line : Collider
{
	Vector2 end_;

	Line() : Collider(Vector2(0, 0)), end_(0, 0) { }
	Line(Vector2 start, Vector2 end) : Collider(start), end_(end) { }
	Line(int start_x, int start_y, int end_x, int end_y) : Collider(Vector2(start_x, start_y)), end_(end_x, end_y) { }
	Line(float start_x, float start_y, float end_x, float end_y) : Collider(Vector2(start_x, start_y)), end_(end_x, end_y) { }
};

struct Rectangle : Collider
{
	Vector2 origin_;
	Vector2 size_;

	Rectangle(Entity& parent) 
	{
		position_ = parent.position_;
		size_ = parent.size_;
		origin_ = parent.origin_;
	}
	Rectangle() : Collider(Vector2(0, 0)), size_(0, 0), origin_(0, 0) { }
	Rectangle(Vector2 position, Vector2 size, Vector2 origin = Vector2(0, 0)) : Collider(position), size_(size), origin_(origin) { }
	Rectangle(int x, int y, int w, int h, int origin_x = 0, int origin_y = 0) : Collider(Vector2(x, y)), size_(w, h), origin_(origin_x, origin_y) { }
	Rectangle(float x, float y, float w, float h, float origin_x = 0.0f, float origin_y = 0.0f) : Collider(Vector2(x, y)), size_(w, h), origin_(origin_x, origin_y) { }
};




#endif // !__COLLIDER__

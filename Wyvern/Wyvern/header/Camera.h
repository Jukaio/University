// Camera.h

#ifndef __CAMERA__
#define __CAMERA__

#include "Vector2.h"

struct Camera
{
	Camera();
	~Camera();

	void Set_Position(Vector2 position);
	Vector2 Get_Position();

	void Set_Size(Vector2 size);
	Vector2 Get_Size();

private:
	Vector2 position_;
	Vector2 size_;
};

#endif // !__CAMERA__

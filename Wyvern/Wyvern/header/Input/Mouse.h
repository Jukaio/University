// Mouse.h

#ifndef __MOUSE__
#define __MOUSE__

#include <Vector2.h>

struct Mouse
{
	Mouse();
	~Mouse();

	//Call those in an Input Handler method for every frame
	void Set_Mouse_Position(int& x, int& y);

	Vector2 Get_Mouse_Position();

private:
	Vector2 position_;

};


#endif // !__MOUSE__
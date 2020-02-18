// Mouse.h

#ifndef __MOUSE__
#define __MOUSE__

#include <Vector2.h>

struct Mouse
{
	//Call this in an Initialisation 
	static void Initialise();

	//Call those in an Input Handler method for every frame
	static void Set_Mouse_Position(int& x, int& y);
	static Vector2 Get_Mouse_Position();

	static void Clean();
private:
	Mouse();
	static Mouse* instance_;

	Vector2 position_;

};


#endif // !__MOUSE__
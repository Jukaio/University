//Keyboard.h

#ifndef __KEYBOARD__
#define __KEYBOARD__

#include <SDL2/SDL_scancode.h>

/*
You receive the info about a certain key and its behaviour through static methods.
The Input Handler refreshes and updates the only instance of a keyboard (A second is not supposed
to exist) and then you can call the wished method through Keyboard::(Insert Method here)
*/

struct Keyboard
{
	Keyboard();
	~Keyboard();

	//Call those in an Input Handler method for every frame
	void Update_Last_Frame();
	void Update_Key(SDL_Scancode key, bool value);

	bool Key_State(SDL_Scancode key);
	bool Key_Pressed(SDL_Scancode key);
	bool Key_Released(SDL_Scancode key);

private:
	bool current_Frame_[SDL_NUM_SCANCODES] = { false };
	bool last_Frame_[SDL_NUM_SCANCODES] = { false };
};


#endif // !__KEYBOARD__

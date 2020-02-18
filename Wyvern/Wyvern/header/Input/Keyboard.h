//Keyboard.h

#ifndef __KEYBOARD__
#define __KEYBOARD__

#include <SDL2/SDL.h>

/*
You receive the info about a certain key and its behaviour through static methods.
The Input Handler refreshes and updates the only instance of a keyboard (A second is not supposed
to exist) and then you can call the wished method through Keyboard::(Insert Method here)
*/

struct Keyboard
{
	//Call this in an Initialisation 
	static void Initialise();

	//Call those in an Input Handler method for every frame
	static void Update();
	static void Update_Key(SDL_Scancode key, bool value);

	static bool Key_State(SDL_Scancode key);
	static bool Key_Pressed(SDL_Scancode key);
	static bool Key_Released(SDL_Scancode key);

	static void Clean();
private:
	Keyboard();
	static Keyboard* instance_;

	bool current_Frame_[SDL_NUM_SCANCODES] = { false };
	bool last_Frame_[SDL_NUM_SCANCODES] = { false };
};


#endif // !__KEYBOARD__

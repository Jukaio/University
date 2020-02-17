//InputHandler.cpp

#include "Input/Input_Handler.h"


Input_Handler::Input_Handler()
{

}

void Input_Handler::Initialise()
{
	Keyboard::Initialise();
}

bool Input_Handler::Handle_Input_Events()
{
	Keyboard::Update();

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:		return false;
			case SDL_KEYDOWN:	Keyboard::Update_Key(event.key.keysym.scancode, true);	break;
			case SDL_KEYUP:		Keyboard::Update_Key(event.key.keysym.scancode, false); break;
		}
	}
	return true;
}


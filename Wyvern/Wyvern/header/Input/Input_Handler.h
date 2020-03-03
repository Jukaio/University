//InputHandler.h

#ifndef __INPUT_HANDLER__
#define __INPUT_HANDLER__

struct Input_Handler
{
	static Input_Handler* instance_;
	
	static void Initialise();
	static bool Handle_Input_Events();
	static void Clean();

private:
	void Get_Mouse_Position();

	Input_Handler();
	~Input_Handler();
};

#endif // !__INPUTHANDLER__






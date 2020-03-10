//InputHandler.h

#ifndef __INPUT_HANDLER__
#define __INPUT_HANDLER__

struct Input_Handler
{
	Input_Handler();
	~Input_Handler();

	bool Handle_Input_Events();

private:
	void Get_Mouse_Position();
};

#endif // !__INPUTHANDLER__






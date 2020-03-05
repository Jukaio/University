// SDL_Pipeline.h

#ifndef __SDL_PIPELINE__
#define __SDL_PIPELINE__

struct SDL_Renderer;
struct SDL_Window;

struct SDL_Pipeline
{
	SDL_Pipeline();
	~SDL_Pipeline();
	SDL_Renderer* Get_Renderer();
	SDL_Window* Get_Window();

private:
	SDL_Renderer* renderer_;
	SDL_Window* window_;
};

#endif // !__SDL_PIPELINE__

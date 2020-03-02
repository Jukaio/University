// Renderer.h

#ifndef __RENDERER__
#define __RENDERER__

struct SDL_Renderer;
struct SDL_Window;

struct Renderer
{
	static void Initialise();

	static SDL_Renderer* Get_Renderer();
	static SDL_Window* Get_Window();

	static void Destroy();

private:
	static SDL_Renderer* renderer_;
	static SDL_Window* window_;

	static bool initialised_;

};


#endif // !__RENDERER__

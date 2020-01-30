//Tile.h

#ifndef __TILE__
#define __TILE__

#include <SDL.h>

struct Tile
{
	int x_, y_;
	int width_, height_;
	
	SDL_Colour colour_;

	Tile();

	void Create(int x, int y, int w, int h,
				int r = 0, int g= 0, int b = 0, int a = 0);
	void Set_Colour(int r, int g, int b, int a);
	void Render(SDL_Renderer* renderer);
};

#endif // !__TILE__

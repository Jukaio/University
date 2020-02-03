//Grid_Manager.h

#ifndef __GRID_MANAGER__
#define _GRID_MANAGER__

#include "Grid.h"

struct Grid_Manager
{
	Grid* grids_;
	unsigned int size_;
	int tile_Size_;

	SDL_Renderer* renderer_;

	Grid_Manager();

	void Create(SDL_Renderer* renderer, int tile_Size);
	void Add_Grid(int x, int y, int w, int h);
	void Plant_Global(int x, int y);


	Tile Get_Tile(int x, int y); // "Global Coordinates" to "Grid Coordinates" aka.
					 // find the coordinate which touches the tile and return it

	void Render();
};



#endif // !__GRID_MANAGER__

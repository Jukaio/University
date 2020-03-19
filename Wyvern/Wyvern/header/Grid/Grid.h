// Grid.h

#ifndef __GRID__
#define __GRID__

#include <vector>
#include "Settings.h"
#include <limits.h>

struct Vector2;

struct Node
{
	unsigned short x_;
	unsigned short y_;
	bool has_Grass_ = false;
	bool has_Wolf_ = false;

	int distance_ = INT_MAX;
	int grass_Level_;
	int distance_to_grass_ = 0;

	std::vector<Node*> neighbours_;
	std::vector<Node*> checked_Neighbours_;

	void Start_Set_Distance();
	void Set_Distance(Node* self = nullptr, std::vector<Node*>* checked_neighbours = nullptr);

	Vector2 Get_Position();
	Vector2 Get_Position_Centered_Origin();
	std::vector<Node*> Get_Neighbours();
};

struct Grid
{
	// Data
	static const short WIDTH_WORLD = Settings::WIDTH;
	static const short HEIGHT_WORLD = Settings::HEIGHT;

	static const short TILE_DIMENSION = 64;

	static const short WIDTH_GRID = WIDTH_WORLD / TILE_DIMENSION;
	static const short HEIGHT_GRID = HEIGHT_WORLD / TILE_DIMENSION;

	Node* nodes_;

	// Methods
	Grid();
	~Grid();

	static Vector2 Global_To_Grid(Vector2 position);
	static Vector2 Grid_To_Global(Vector2 position);
	Node* Get_Node(Vector2 position);

	void Render_Nodes();
};


#endif // !__GRID__

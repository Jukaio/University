// Grid.cpp

#include "Grid/Grid.h"
#include "Vector2.h"
#include "Service.h"
#include "Engine/SDL_Pipeline.h"
#include <SDL2/SDL.h>

Grid::Grid()
{
	nodes_ = new Node[HEIGHT_GRID * WIDTH_GRID];

	// Set position of nodes
	for (int x = 0; x < WIDTH_GRID; x++)
	{
		for (int y = 0; y < HEIGHT_GRID; y++)
		{
			nodes_[y * WIDTH_GRID  + x].x_ = x * TILE_DIMENSION;
			nodes_[y * WIDTH_GRID  + x].y_ = y * TILE_DIMENSION;
		}
	}

	// Set neighbours of nodes
	for (int x = 0; x < WIDTH_GRID; x++)
	{
		for (int y = 0; y < HEIGHT_GRID; y++)
		{
			// Horizontally and Vertically
			if (y > 0)
				nodes_[y * WIDTH_GRID + x].neighbours_.push_back(&nodes_[(y - 1) * WIDTH_GRID + (x + 0)]);
			if (y < HEIGHT_GRID - 1)
				nodes_[y * WIDTH_GRID + x].neighbours_.push_back(&nodes_[(y + 1) * WIDTH_GRID + (x + 0)]);
			if (x > 0)
				nodes_[y * WIDTH_GRID + x].neighbours_.push_back(&nodes_[(y + 0) * WIDTH_GRID + (x - 1)]);
			if (x < WIDTH_GRID - 1)
				nodes_[y * WIDTH_GRID + x].neighbours_.push_back(&nodes_[(y + 0) * WIDTH_GRID + (x + 1)]);

			// Diagonally
			if (y > 0 && x > 0)
				nodes_[y * WIDTH_GRID + x].neighbours_.push_back(&nodes_[(y - 1) * WIDTH_GRID + (x - 1)]);
			if (y < HEIGHT_GRID - 1 && x > 0)
				nodes_[y * WIDTH_GRID + x].neighbours_.push_back(&nodes_[(y + 1) * WIDTH_GRID + (x - 1)]);
			if (y > 0 && x <  WIDTH_GRID - 1)
				nodes_[y * WIDTH_GRID + x].neighbours_.push_back(&nodes_[(y - 1) * WIDTH_GRID + (x + 1)]);
			if (y < HEIGHT_GRID - 1 && x < WIDTH_GRID - 1)
				nodes_[y * WIDTH_GRID + x].neighbours_.push_back(&nodes_[(y + 1) * WIDTH_GRID + (x + 1)]);
		}
	}
}

Grid::~Grid()
{
	delete[] nodes_;
}

Vector2 Grid::Global_To_Grid(Vector2 position)
{
	Vector2 temp = position / TILE_DIMENSION;
	return Vector2((int)temp.x_, (int)temp.y_);
}

Vector2 Grid::Grid_To_Global(Vector2 position)
{
	Vector2 temp = position * TILE_DIMENSION;
	return Vector2(temp.x_ + TILE_DIMENSION / 2, temp.y_ + TILE_DIMENSION);
}

Node* Grid::Get_Node(Vector2 position)
{
	int index = (((int)position.y_ * WIDTH_GRID) + (int)position.x_);

	return &nodes_[index];
}

void Grid::Render_Nodes()
{
	SDL_Rect dst_rect;
	Node node;

	dst_rect.w = TILE_DIMENSION;
	dst_rect.h = TILE_DIMENSION;

	for (int x = 0; x < WIDTH_GRID; x++)
	{
		for (int y = 0; y < HEIGHT_GRID; y++)
		{
			node = nodes_[y * WIDTH_GRID + x];
			dst_rect.x = node.x_;
			dst_rect.y = node.y_;

			SDL_SetRenderDrawColor(Service<SDL_Pipeline>::Get()->Get_Renderer(), 255, 0, 0, 255);
			SDL_RenderDrawRect(Service<SDL_Pipeline>::Get()->Get_Renderer(), &dst_rect);
		}
	}
}

bool Check_Neighbours(Node* to_check, std::vector<Node*>* listp)
{
	std::vector<Node*> list = *listp;
	for (auto&& item : list)
	{
		if (item == to_check)
			return false;
	}
	return true;
}

int Count_Steps(Node* parent, Node* child)
{

	return (int)parent->Get_Position().Distance_To(child->Get_Position());
}


void Node::Start_Set_Distance() //Call in the parent node
{
	distance_ = 0;

	for (auto&& node : neighbours_)
	{
		node->Set_Distance(this, &checked_Neighbours_);
	}
	checked_Neighbours_.clear();
}

void Node::Set_Distance(Node* parent, std::vector<Node*>* checked_neighbours)
{
	for (auto&& node : neighbours_)
	{
		if (node == parent)
			continue;
		
		if (Check_Neighbours(node, checked_neighbours))
		{
			int distance = Count_Steps(parent, node);
			//if (distance < distance_)
				node->distance_ = distance;

			checked_neighbours->push_back(node);

			node->Set_Distance(parent, checked_neighbours);
		}
	}
}


Vector2 Node::Get_Position()
{
	return Vector2(x_, y_);
}

Vector2 Node::Get_Position_Centered_Origin()
{
	return Vector2(x_ + (Grid::TILE_DIMENSION / 2), y_ + (Grid::TILE_DIMENSION / 2));
}

std::vector<Node*> Node::Get_Neighbours()
{
	return neighbours_;
}

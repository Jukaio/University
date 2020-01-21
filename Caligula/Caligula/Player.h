//Player.h
#ifndef __PLAYER__
#define __PLAYER__

#include "Entity.h";

struct Player : Entity
{
	Player();

	void Create(int x, int y, float scale, bool active, bool visible, const char* file_Path,
				Collider* collider, EntityType type);
	void Update();
	void Render(SDL_Renderer* renderer);

};

#endif // !__PLAYER__





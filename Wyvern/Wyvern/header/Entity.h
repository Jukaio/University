// Entity.h

#ifndef __ENTITY__
#define __ENTITY__

#include "IEntity.h"

struct SDL_Renderer;

struct Entity : IEntity
{
	void Create();
	void Create(Vector2 position, Vector2 size);
	void Create(Vector2 position, float w, float h);
	void Create(float x, float y, Vector2 size);
	void Create(float x, float y, float w, float h);
	void Create(int x, int y, int w, int h);

	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* renderer) = 0;


};


#endif // !__ENTITY__
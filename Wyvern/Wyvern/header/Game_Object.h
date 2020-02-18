// Game_Object.h

#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Entity.h"

struct Game_Object : Entity
{
	Game_Object();
	Game_Object(Vector2 position, Vector2 size);
	Game_Object(Vector2 position, float w, float h);
	Game_Object(float x, float y, Vector2 size);
	Game_Object(float x, float y, float w, float h);
	Game_Object(int x, int y, int w, int h);

	virtual void Update();
	virtual void Render(SDL_Renderer* renderer);

	void Set_Origin(Vector2 origin);
	void Set_Origin(int x, int y);
	void Set_Origin(float x, float y);
};


#endif // !__GAME_OBJECT__

// Game_Object.h

#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "Entity.h"
#include "Collision_Detection/Collider.h"

struct Collider;

struct Game_Object : Entity
{
	Game_Object* parent_;
	Rectangle collider_;

	Game_Object();
	Game_Object(Vector2 position, Vector2 size, Vector2 origin = Vector2(0,0), Game_Object* parent = nullptr);

	virtual void Update();
	virtual void Render();

	void Set_Origin(Vector2 origin);
	void Set_Origin(int x, int y);
	void Set_Origin(float x, float y);
};


#endif // !__GAME_OBJECT__

// Component.h

#ifndef __COMPONENT__
#define __COMPONENT__

struct Game_Object;

struct Component
{
	Game_Object& game_Object_;

	Component(Game_Object& game_Object_)
		: game_Object_(game_Object_)
	{

	}

	virtual ~Component()
	{

	}
};


#endif // !__COMPONENT__

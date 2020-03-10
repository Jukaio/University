// Entity.h

#ifndef __ENTITY__
#define __ENTITY__

struct Wyvern_Game;

struct Entity 
{
	Wyvern_Game* game_;
	Entity() : game_(nullptr) {};

	virtual void Update() = 0;
	virtual void Render() = 0;
};


#endif // !__ENTITY__
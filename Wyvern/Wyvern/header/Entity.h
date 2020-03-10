// Entity.h

#ifndef __ENTITY__
#define __ENTITY__

struct Entity 
{
	Entity() {};

	virtual void Update() = 0;
	virtual void Render() = 0;
};


#endif // !__ENTITY__
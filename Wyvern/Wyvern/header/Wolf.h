// Wolf.h

#ifndef __WOLF__
#define __WOLF__

#include "Game_Object.h"

struct Wolf : Game_Object
{
	Wolf(Wyvern_Game* game);
	~Wolf();

	// Loop
	virtual void Update() override;
	virtual void Render() override;

};

#endif // !__WOLF__

// IEntity.h

#ifndef __IENTITY__
#define __IENTITY__

#include "Vector2.h"

// Entity parameters
struct IEntity
{
	Vector2 position_;
	Vector2 size_;
	int Texture_ID_;

	IEntity();

};


#endif // !__IENTITY__
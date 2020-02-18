// IEntity.h

#ifndef __IENTITY__
#define __IENTITY__

#include "Vector2.h"

// Entity parameters
struct IEntity
{
	IEntity();

	Vector2 origin_;
	Vector2 position_;
	Vector2 size_;
	int Texture_ID_;

};


#endif // !__IENTITY__
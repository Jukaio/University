// IEntity.h

#ifndef __IENTITY__
#define __IENTITY__

#include <Components/Component.h>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

// Entity parameters
struct IEntity
{
public:
	IEntity();
	~IEntity() { }
};


#endif // !__IENTITY__
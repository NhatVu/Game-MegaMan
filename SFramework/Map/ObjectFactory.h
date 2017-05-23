#ifndef _OBJECT_FACTORY_H_
#define _OBJECT_FACTORY_H_
#include "../GameObject.h"
#include "../../MegaMan/MegaManUtilities.h"

namespace s_framework{

class ObjectFactory
{
private:
	ObjectFactory();

public:
	static GameObject* createObject(int objectType);
	~ObjectFactory();
};
}

#endif // !_OBJECT_FACTORY_H_

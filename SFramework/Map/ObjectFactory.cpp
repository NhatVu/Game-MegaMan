#include "ObjectFactory.h"
#include "../../MegaMan/GameObject/Kamadoma.h"
#include "../../MegaMan/GameObject/MegaManBullet.h"
#include "../../MegaMan/MegaManUtilities.h"
using namespace s_framework;
ObjectFactory::ObjectFactory()
{
}


ObjectFactory::~ObjectFactory()
{
}

GameObject* ObjectFactory::createObject(int objectType){
	GameObject* object = NULL;
	switch (objectType)
	{
	case ECharacter::LADDER:
	case ECharacter::STATIC:
		object = new GameObject();
		break;
	case ECharacter::KAMADOMA:
		object = new Kamadoma();
		((Kamadoma*)object)->setState(EState::ACTIVE);
		break;
	case ECharacter::MEGAMAN_BULLET:
		object = new MegaManBullet();
		break;
	default:
		break;
	}
	return object;
}

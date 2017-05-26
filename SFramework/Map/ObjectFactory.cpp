#include "ObjectFactory.h"
#include "../../MegaMan/GameObject/Kamadoma.h"
#include "../../MegaMan/GameObject/MegaManBullet.h"
#include "../../MegaMan/MegaManUtilities.h"
#include "../../MegaMan/GameObject/BombombombParent.h"
#include "../SpriteAndAnimation/TextureManager.h"
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
		//((Kamadoma*)object)->setState(EState::ACTIVE);
		object->setState(EState::ACTIVE);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	case ECharacter::MEGAMAN_BULLET:
		object = new MegaManBullet();
		//((MegaManBullet*)object)->setState(EState::ACTIVE);
		object->setState(EState::ACTIVE);
		object->setType(ECharacter::MEGAMAN_BULLET);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	case ECharacter::BOMBOMBOMB_PARENT:
		object = new BombombombParent();
		object->setState(EState::ACTIVE);
		object->setType(ECharacter::BOMBOMBOMB_PARENT);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
	default:
		break;
	}
	return object;
}

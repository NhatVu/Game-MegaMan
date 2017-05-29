#include "ObjectFactory.h"
#include "../../MegaMan/GameObject/Kamadoma.h"
#include "../../MegaMan/GameObject/MegaManBullet.h"
#include "../../MegaMan/MegaManUtilities.h"
#include "../../MegaMan/GameObject/BombombombParent.h"
#include "../../MegaMan/GameObject/BombombombChildren.h"
#include "../../MegaMan/GameObject/Blader.h"
#include "../SpriteAndAnimation/TextureManager.h"
#include "../../MegaMan/GameObject/Blaster.h"
#include "../../MegaMan/GameObject/BlasterBullet.h"
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
		break;
	case ECharacter::BOMBOMBOM_CHILDREN:
		object = new BombombombChildren();
		object->setState(EState::ACTIVE);
		object->setType(ECharacter::BOMBOMBOM_CHILDREN);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	case ECharacter::BLADER:
		object = new Blader();
		object->setState(EState::ACTIVE);
		object->setType(ECharacter::BLADER);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	case ECharacter::BLASTER:
		object = new Blaster();
		object->setState(EState::IDLE);
		object->setType(ECharacter::BLASTER);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	case ECharacter::BLASTER_BULLET:
		object = new Blaster();
		object->setState(EState::ACTIVE);
		object->setType(ECharacter::BLASTER_BULLET);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	default:
		break;
	}
	return object;
}

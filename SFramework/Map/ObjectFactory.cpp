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
#include "../../MegaMan/GameObject/Suzy.h"
#include "../../MegaMan/GameObject/Screw.h"
#include "../../MegaMan/GameObject/ScrewBullet.h"
#include "../../MegaMan/GameObject/FlyShell.h"
#include "../../MegaMan/GameObject/FlyShellBullet.h"
#include "../../MegaMan/GameObject/SuperCutter.h"
#include "../../MegaMan/GameObject/SupperCutterFactory.h"
#include "../../MegaMan/GameObject/BigEye.h"
#include "../../MegaMan/GameObject/CutMan.h"
#include "../../MegaMan/GameObject/CutManCut.h"
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
		object = new BlasterBullet();
		object->setState(EState::ACTIVE);
		object->setType(ECharacter::BLASTER_BULLET);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	case ECharacter::SUZY:
		object = new Suzy();
		object->setState(EState::ACTIVE);
		object->setType(ECharacter::SUZY);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	case ECharacter::SCREW:
		object = new Screw();
		object->setState(EState::ACTIVE);
		object->setType(ECharacter::SCREW);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	case ECharacter::SCREW_BULLET:
		object = new ScrewBullet();
		object->setState(EState::ACTIVE);
		object->setType(ECharacter::SCREW_BULLET);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	case ECharacter::FLY_SHELL:
		object = new FlyShell();
		object->setState(EState::IDLE);
		object->setType(ECharacter::FLY_SHELL);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	case ECharacter::FLY_SHELL_BULLET:
		object = new FlyShellBullet();
		object->setState(EState::ACTIVE);
		object->setType(ECharacter::FLY_SHELL_BULLET);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	case ECharacter::SUPER_CUTTER_FACTORY:
		object = new SupperCutterFactory();
		object->setType(ECharacter::SUPER_CUTTER_FACTORY);

		break;
	case ECharacter::SUPER_CUTTER:
		object = new SuperCutter();
		object->setState(EState::ACTIVE);
		object->setType(ECharacter::SUPER_CUTTER);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	case ECharacter::BIG_EYE:
		object = new BigEye();
		object->setState(EState::ACTIVE);
		object->setType(ECharacter::BIG_EYE);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	case ECharacter::CUTMAN:
		object = new CutMan();
		object->setState(EState::IDLE);
		object->setType(ECharacter::CUTMAN);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	case ECharacter::CUTMAN_CUT:
		object = new CutManCut();
		object->setState(EState::IDLE);
		object->setType(ECharacter::CUTMAN_CUT);
		object->setTexture(TextureManager::getInstance()->getObjectTexture());
		break;
	default:
		break;
	}
	return object;
}

#include "Utilities.h"
#ifndef _COLLISION_H_
#define _COLLISION_H_
#include "GameObject.h"

namespace s_framework{

class Collision
{
public:
	
	static float CheckCollision(GameObject* mDynamic, GameObject* mStatic, D3DXVECTOR2 &normal);
	static float SweptAABB(BOX b1, BOX b2, float& normalx, float& normaly);
	~Collision();
	static void GetBoxesSweptAABB(GameObject* _dynamicObject, GameObject* _staticObject, BOX& _dynamicBox, BOX& _staticBox);
	static bool CheckBroadPhasing(BOX _b1, BOX _b2);
	static BOX GetBroadPhasing(BOX b);
private:
	Collision();
};
}
#endif
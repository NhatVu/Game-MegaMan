#include "Collision.h"

using namespace s_framework;
Collision::Collision()
{
}

//// ok
//void Collision::getCollisionBoxesSweptAABB(GameObject* _dynamicObject, GameObject* _staticObject, BOX& _dynamicBox, BOX& _staticBox)
//{
//	_dynamicBox = _dynamicObject->getCollisionBox();
//	_staticBox = _staticObject->getCollisionBox();
//	_dynamicBox.getV vx = (_dynamicBox.vx - _staticBox.vx)* CGameTime::GetInstance()->GetTimePerFrame();
//	_dynamicBox.vy = (_dynamicBox.vy - _staticBox.vy)* CGameTime::GetInstance()->GetTimePerFrame();
//	_staticBox.vx = 0;
//	_staticBox.vy = 0;
//}

// returns a box the spans both a current box and the destination box
// ok
BOX Collision::GetBroadPhasing(BOX b)
{
	BOX broadphasebox;
	
	broadphasebox.x = b.vx > 0 ? b.x : b.x + b.vx;
	broadphasebox.y = b.vy > 0 ? b.y + b.vy: b.y;
	broadphasebox.width = b.vx > 0 ? b.vx + b.width : b.width - b.vx;
	broadphasebox.height = b.vy > 0 ? b.vy + b.height : b.height - b.vy;
	
	return broadphasebox;
}

// returns true if a collision occurred.

bool Collision::CheckBroadPhasing(BOX _b1, BOX _b2)// ok
{
	return !(_b1.x + _b1.width < _b2.x || _b1.x > _b2.x + _b2.width || _b1.y - _b1.height > _b2.y || 
		_b2.y - _b2.height > _b1.y);

}


float Collision::SweptAABB(BOX _b1, BOX _b2, float& normalx, float& normaly)
{
	/*fstream f;
	f.open("output.txt", ios::app);
	std::string data;
	data = "\n\nTimeDelta: " + std::to_string(CGameTime::GetInstance()->GetDeltaTime());
	data += "\nbox 1. x: " + std::to_string(_b1.x) + "  y: " + std::to_string(_b1.y);
	data += "\nbox 2. x: " + std::to_string(_b2.x) + "  y: " + std::to_string(_b2.y);
	f << data;
	f.close();*/
	
	float xInvEntry, yInvEntry;
	float xInvExit, yInvExit;
	if (_b1.vx > 0.0f)
	{
		xInvEntry = _b2.x - (_b1.x + _b1.width);
		xInvExit = (_b2.x + _b2.width) - _b1.x;
	}
	else
	{
		xInvEntry = (_b2.width + _b2.x) - _b1.x;
		xInvExit = _b2.x - (_b1.x + _b1.width);
	}

	if (_b1.vy > 0.0f)
	{
		yInvEntry = (_b2.y - _b2.height) - _b1.y;
		yInvExit = _b2.y - (_b1.y - _b1.height);
		//yInvEntry = b2.y - (b1.y + b1.h);
		//yInvExit = _b2.y - (_b1.y - _b1.h);
	}
	else
	{
		yInvEntry = _b2.y - (_b1.y - _b1.height);
		yInvExit = (_b2.y - _b2.height) - _b1.y;
		//yInvEntry = _b2.y - (_b1.y - _b1.h);
		//yInvExit = _b1.y - (_b2.y - _b2.h);
	}////////// ok

	float xEntry, yEntry;
	float xExit, yExit;

	if (_b1.vx == 0.0f)
	{
		xEntry = -std::numeric_limits<float>::infinity();
		xExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		xEntry = xInvEntry / (_b1.vx); // phan mau la pixel/frame
		xExit = xInvExit / (_b1.vx);
	}

	if (_b1.vy == 0.0f)
	{
		yEntry = -std::numeric_limits<float>::infinity();
		yExit = std::numeric_limits<float>::infinity();
	}
	else
	{
		yEntry = yInvEntry / (_b1.vy );
		yExit = yInvExit / (_b1.vy );
	}

	float entryTime = max(xEntry, yEntry);
	float exitTime = min(xExit, yExit);

	if ((entryTime > exitTime) || xEntry < 0 && yEntry < 0 || xEntry > 1 || yEntry > 1)
	
	{	
		normalx = 0.0f;
		normaly = 0.0f;
		return 1.0f;
	}
	else
	{
		// if there was a collision
		if (xEntry > yEntry)
		{
			if (yInvEntry < 0.0f){
				if (xInvEntry < 0.0f)
				{ // vật đi từ bên phải sang, với vx < 0
					normalx = 1.0f;
					normaly = 0.0f;
				}
				else
				{ // vật đi từ bên trái sang, với vx > 0
					normalx = -1.0f;
					normaly = 0.0f;
				}
			}
		}
		else
		{
			if (xInvEntry < 0.0f){
				if (yInvEntry < 0.0f)
				{ // vật đi từ trên xuống, vy < 0
					normalx = 0.0f;
					normaly = 1.0f;
				}
				else
				{ // vật đi từ dưới lên, vy > 0
					normalx = 0.0f;
					normaly = -1.0f;
				}
			}
		}
	}
	return entryTime;
}  




float Collision::CheckCollision(GameObject* mDynamic, GameObject* mStatic, D3DXVECTOR2 &normal)
{
	BOX dynamicBox = mDynamic->getCollisionBox();
	BOX staticBox = mDynamic->getCollisionBox();

	BOX broadPhaseBox = GetBroadPhasing(dynamicBox);
	float timeCollision;
	if (CheckBroadPhasing(broadPhaseBox, staticBox))
	{
		timeCollision = SweptAABB(dynamicBox, staticBox, normal.x, normal.y);
		//_base->SetTimeCollision(TimeCollision);
	}
	return timeCollision;

}

Collision::~Collision()
{
}

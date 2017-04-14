//#include "Collision.h"
//
//
//CCollision::CCollision()
//{
//}
//
//// ok
//void CCollision::GetBoxesSweptAABB(CGameObject* _dynamicObject, CGameObject* _staticObject, BOX& _dynamicBox, BOX& _staticBox)
//{
//	_dynamicBox = _dynamicObject->GetBox();
//	_staticBox = _staticObject->GetBox();
//	_dynamicBox.vx = (_dynamicBox.vx - _staticBox.vx)* CGameTime::GetInstance()->GetTimePerFrame();
//	_dynamicBox.vy = (_dynamicBox.vy - _staticBox.vy)* CGameTime::GetInstance()->GetTimePerFrame();
//	_staticBox.vx = 0;
//	_staticBox.vy = 0;
//}
//
//// returns a box the spans both a current box and the destination box
//// ok
//BOX CCollision::GetBroadPhasing(BOX b)
//{
//	BOX broadphasebox;
//	
//	broadphasebox.x = b.vx > 0 ? b.x : b.x + b.vx;
//	broadphasebox.y = b.vy > 0 ? b.y + b.vy: b.y;
//	broadphasebox.w = b.vx > 0 ? b.vx + b.w : b.w - b.vx;
//	broadphasebox.h = b.vy > 0 ? b.vy + b.h : b.h - b.vy;
//	if (b.x <= 156.08 && b.x > 156)
//	{
//		int a = 2;
//	}
//	return broadphasebox;
//}
//
//// returns true if a collision occurred.
//
//bool CCollision::CheckBroadPhasing(BOX _b1, BOX _b2)// ok
//{
//	return !(_b1.x + _b1.w < _b2.x || _b1.y - _b1.h > _b2.y || _b1.x > _b2.x + _b2.w || _b1.y < _b2.y - _b2.h);
//
//}
//
//#pragma region SweptAABB
//
//float CCollision::SweptAABB(BOX _b1, BOX _b2, float& normalx, float& normaly)
//{
//	/*fstream f;
//	f.open("output.txt", ios::app);
//	std::string data;
//	data = "\n\nTimeDelta: " + std::to_string(CGameTime::GetInstance()->GetDeltaTime());
//	data += "\nbox 1. x: " + std::to_string(_b1.x) + "  y: " + std::to_string(_b1.y);
//	data += "\nbox 2. x: " + std::to_string(_b2.x) + "  y: " + std::to_string(_b2.y);
//	f << data;
//	f.close();*/
//	if (_b2.x < 93 && _b2.y >70 )
//	{
//		int a = 2;
//	}
//	float xInvEntry, yInvEntry;
//	float xInvExit, yInvExit;
//	if (_b1.vx > 0)
//	{
//		xInvEntry = _b2.x - (_b1.x + _b1.w);
//		xInvExit = (_b2.x + _b2.w) - _b1.x;
//	}
//	else
//	{
//		xInvEntry = (_b2.w + _b2.x) - _b1.x;
//		xInvExit = _b2.x - (_b1.x + _b1.w);
//	}
//
//	if (_b1.vy > 0)
//	{
//		yInvEntry = (_b2.y - _b2.h) - _b1.y;
//		yInvExit = _b2.y - (_b1.y - _b1.h);
//		//yInvEntry = _b1.y - (_b2.y - _b2.h);
//		//yInvExit = _b2.y - (_b1.y - _b1.h);
//	}
//	else
//	{
//		yInvEntry = _b2.y - (_b1.y - _b1.h);
//		yInvExit = (_b2.y - _b2.h) - _b1.y;
//		//yInvEntry = _b2.y - (_b1.y - _b1.h);
//		//yInvExit = _b1.y - (_b2.y - _b2.h);
//	}
//
//	float xTimeEntry, yTimeEntry;
//	float xTimeExit, yTimeExit;
//
//	if (_b1.vx == 0)
//	{
//		xTimeEntry = -std::numeric_limits<float>::infinity();
//		xTimeExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		xTimeEntry = xInvEntry / (_b1.vx); // phan mau la pixel/frame
//		xTimeExit = xInvExit / (_b1.vx);
//	}
//
//	if (_b1.vy == 0)
//	{
//		yTimeEntry = -std::numeric_limits<float>::infinity();
//		yTimeExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		yTimeEntry = yInvEntry / (_b1.vy );
//		yTimeExit = yInvExit / (_b1.vy );
//	}
//
//	float entryTime = max(xTimeEntry, yTimeEntry);
//	float exitTime = min(xTimeExit, yTimeExit);
//
//	if ((entryTime > exitTime) || xTimeEntry < 0 && yTimeEntry < 0 || xTimeEntry > 1 || yTimeEntry > 1)
//	
//	{	
//		normalx = 0;
//		normaly = 0;
//		return 1;
//	}
//	else
//	{
//		if (xTimeEntry > yTimeEntry)
//		{
//			if (yInvEntry != 0){
//				if (xInvEntry < 0)
//				{
//					normalx = 1;
//					normaly = 0;
//				}
//				else
//				{
//					normalx = -1;
//					normaly = 0;
//				}
//			}
//		}
//		else
//		{
//			if (xInvEntry != 0){
//				if (yInvEntry < 0)
//				{
//					normalx = 0;
//					normaly = 1;
//				}
//				else
//				{
//					normalx = 0;
//					normaly = -1;
//				}
//			}
//		}
//	}
//	return entryTime;
//}  
//#pragma endregion
//
////float CCollision::SweptAABB(BOX b1, BOX b2, float& normalx, float& normaly)
////{
////	float xInvEntry, yInvEntry;
////	float xInvExit, yInvExit;
////
////	// find the distance between the objects on the near and far sides for both x and y
////	if (b1.vx > 0.0f)
////	{
////		xInvEntry = b2.x - (b1.x + b1.w);
////		xInvExit = (b2.x + b2.w) - b1.x;
////	}
////	else
////	{
////		xInvEntry = (b2.x + b2.w) - b1.x;
////		xInvExit = b2.x - (b1.x + b1.w);
////	}
////
////	if (b1.vy > 0.0f)
////	{
////		yInvEntry = (b2.y - b2.h) - b1.y;
////		yInvExit = b2.y - (b1.y - b1.h);
////	}
////	else
////	{
////		yInvEntry = b2.y - (b1.y - b1.h);
////		yInvExit = (b2.y - b2.h) - b1.y;
////	}
////
////	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
////	float xEntry, yEntry;
////	float xExit, yExit;
////
////	if (b1.vx == 0.0f)
////	{
////		xEntry = -std::numeric_limits<float>::infinity();
////		xExit = std::numeric_limits<float>::infinity();
////	}
////	else
////	{
////		xEntry = xInvEntry / b1.vx;
////		xExit = xInvExit / b1.vx;
////	}
////
////	if (b1.vy == 0.0f)
////	{
////		yEntry = -std::numeric_limits<float>::infinity();
////		yExit = std::numeric_limits<float>::infinity();
////	}
////	else
////	{
////		yEntry = yInvEntry / b1.vy;
////		yExit = yInvExit / b1.vy;
////	}
////
////	// find the earliest/latest times of collision
////	float entryTime = max(xEntry, yEntry);
////	float exitTime = min(xExit, yExit);
////
////	// if there was no collision
////	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
////	{
////		normalx = 0.0f;
////		normaly = 0.0f;
////		return 1.0f;
////	}
////	else // if there was a collision
////	{
////		// calculate normal of collided surface
////		if (xEntry > yEntry)
////		{
////			if (xInvEntry < 0.0f)
////			{
////				normalx = 1.0f;
////				normaly = 0.0f;
////			}
////			else
////			{
////				normalx = -1.0f;
////				normaly = 0.0f;
////			}
////		}
////		else
////		{
////			if (yInvEntry <= 0.0f)
////			{
////				normalx = 0.0f;
////				normaly = 1.0f;
////			}
////			else
////			{
////				normalx = 0.0f;
////				normaly = -1.0f;
////			}
////		}
////
////		// return the time of collision
////		return entryTime;
////	}
////}
//
//EDIRECTORY CCollision::CheckCollision(CGameObject* _base, CGameObject* _other)
//{
//	BOX dynamicBox;
//	BOX staticBox;
//	D3DXVECTOR2 normal;
//	D3DXVECTOR2 move;
//	GetBoxesSweptAABB(_base, _other, dynamicBox, staticBox);
//	fstream f;
//	f.open("output.txt", ios::app);
//	std::string data;
//	data = "\n\nTimeDelta: " + std::to_string(CGameTime::GetInstance()->GetDeltaTime());
//	data += "\nbox 1. x: " + std::to_string(dynamicBox.x) + "  y: " + std::to_string(dynamicBox.y);
//	data += "\nbox 2. x: " + std::to_string(staticBox.x) + "  y: " + std::to_string(staticBox.y);
//	f << data;
//	f.close();
//	/*if (CheckBroadPhasing(dynamicBox, staticBox)==false)
//		return EDIRECTORY::DIR_NONE;*/
//	/*if ((dynamicBox.vx > 0 && (dynamicBox.x + dynamicBox.w > staticBox.x)
//		|| (dynamicBox.vx < 0 && dynamicBox.x < staticBox.x + staticBox.w)))
//		return EDIRECTORY::DIR_NONE;*/
//	if (CheckBroadPhasing(GetBroadPhasing(dynamicBox), staticBox))
//	{
//		float TimeCollision = SweptAABB(dynamicBox, staticBox, normal.x, normal.y);
//		_base->SetTimeCollision(TimeCollision);
//		//if (CheckBroadPhasing(dynamicBox, staticBox) == false)
//		//{
//		//	/*if (TimeCollision < 0 || TimeCollision > 1)
//		//	{
//		//		return EDIRECTORY::DIR_NONE;
//		//	}*/
//		//	return EDIRECTORY::DIR_NONE;
//		//}
//		if (normal.x == 0 && normal.y == 0)
//			return EDIRECTORY::DIR_IN_BROARD_PHASING;
//		
//		if (normal.x == -1)
//		{
//			return EDIRECTORY::DIR_RIGHT;
//		}
//		if (normal.x == 1)
//		{
//			return EDIRECTORY::DIR_LEFT;
//		}
//		if (normal.y == -1)
//		{
//			return EDIRECTORY::DIR_TOP;
//		}
//		if (normal.y == 1)
//		{
//			return EDIRECTORY::DIR_BOTTOM;
//		}
//	}
//	return EDIRECTORY::DIR_NONE;
//}
//
//CCollision::~CCollision()
//{
//}

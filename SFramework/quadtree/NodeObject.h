#pragma once
#include "../GameObject.h"



namespace s_framework
{
	class NodeObject
	{
	private:
		int mId;
		GameObject* mGameObject;
	public:
		NodeObject();
		~NodeObject();
		NodeObject(int id, GameObject*&);
		int getId()
		{
			return mId;
		}

		GameObject* getGameObject()
		{
			return this->mGameObject;
		}
	};
}


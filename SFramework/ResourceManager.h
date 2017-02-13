#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <string>
#include <map>
#include "Animation.h"
#include "AnimationSpec.h"

using namespace std;

namespace s_framework{
	struct ObjectState{
		int m_objectType;
		int    m_state;

		bool operator < (const ObjectState& param)const
		{
			if (m_objectType < param.m_objectType) return true;
			if (m_objectType > param.m_objectType) return false;
			if (m_state < param.m_state) return true;
			return false;
		}
	};

	class ResourceManager
	{
	private:
		static ResourceManager* m_instance;
		map<ObjectState, AnimationSpec*> m_mapAnimationToListSprite;

		/*   method    */
		ResourceManager();
		void parseAnimationXML(string xmlFile);
	public:
		static ResourceManager* getInstance();
		static void resetResourceManager();
		~ResourceManager();
	};

	
}
#endif // !_RESOURCE_MANAGER_H_




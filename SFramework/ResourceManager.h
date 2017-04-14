#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <string>
#include <map>
#include "SpriteAndAnimation/AnimationSpec.h"
#include <list>
#include <vector>
using namespace std;

namespace s_framework{
	struct ObjectState{
		int m_character;
		int    m_state;

		bool operator < (const ObjectState& param)const
		{
			if (m_character < param.m_character) return true;
			if (m_character > param.m_character) return false;
			if (m_state < param.m_state) return true;
			return false;
		}
	};

	class ResourceManager
	{
	private:
		static ResourceManager* m_instance;
		map<ObjectState, AnimationSpec*> m_mapStateToAnimation;

		/*   method    */
		ResourceManager();
	public:
		void parseAnimationJSON(Texture* texture, string jsonFile);
		static ResourceManager* getInstance();
		AnimationSpec* getAnimationSprites(int character, int state);
		static void resetResourceManager();
		~ResourceManager();
	};

	
}
#endif // !_RESOURCE_MANAGER_H_




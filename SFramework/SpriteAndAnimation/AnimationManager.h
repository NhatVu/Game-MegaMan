#ifndef _ANIMATION_MANAGER_H_
#define _ANIMATION_MANAGER_H_

#include <string>
#include <map>
#include "AnimationSpec.h"
#include <list>
#include <vector>
using namespace std;

namespace s_framework{
	
	class AnimationManager
	{
	private:
		static AnimationManager* m_instance;
		map<ObjectState, AnimationSpec*> m_mapStateToAnimation;

		/*   method    */
		AnimationManager();
	public:
		void parseAnimationJSON(Texture* texture, string jsonFile);
		static AnimationManager* getInstance();
		AnimationSpec* getAnimationSprites(int character, int state);
		static void resetResourceManager();
		~AnimationManager();
	};

	
}
#endif // !_ANIMATION_MANAGER_H_




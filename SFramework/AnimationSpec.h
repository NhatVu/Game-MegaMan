#ifndef _ANIMATION_SPEC_H_
#define _ANIMATION_SPEC_H_

#include <vector>
#include "SpriteSpec.h"

using namespace std;

namespace s_framework{

	class AnimationSpec
	{
	private:
		vector<SpriteSpec*> m_spriteSpecs; 		// danh sách chứa SpriteSpec của 1 animation của 1 đối tượng. 
		int m_delayTime;						// thời gian delay giữa 2 frame. tính bằng milis
	public:
		/*-------------------------------------------
			GETTERS AND SETTERS
		---------------------------------------------*/
		int getDelayTime();
		void setDelayTime(int a);

		vector<SpriteSpec*> getSpriteSpecs();
		void setSpriteSpecs(vector<SpriteSpec*> a);
		void addSpriteSpec(SpriteSpec* a);

		AnimationSpec();
		~AnimationSpec();
	};
}
#endif // !_ANIMATION_SPEC_H_




#ifndef _ANIMATION_SPEC_H_
#define _ANIMATION_SPEC_H_

#include <vector>
#include "SpriteSpec.h"
#include "../GameObject.h"

using namespace std;

namespace s_framework{

	class AnimationSpec
	{
	private:
		vector<SpriteSpec*> m_spriteSpecs; 		// danh sách chứa SpriteSpec của 1 animation của 1 đối tượng trong 1 trạng thái  
		int m_delayFrame = 0;						// delay frame
		int m_currentIndex = 0;	
	
		void nextFrame();						// cập nhật lại chỉ số của frame tiếp theo
		int currentDelay = 0;
	public:
		/*-------------------------------------------
			GETTERS AND SETTERS
		---------------------------------------------*/
		int getDelayFrame();
		void setDelayFrame(int a);

		vector<SpriteSpec*> getSpriteSpecs();
		void setSpriteSpecs(vector<SpriteSpec*> a);
		void addSpriteSpec(SpriteSpec* a);

		/*---------------------------------------------
		 *LOGICS
		 ----------------------------------------------*/

		SpriteSpec* getCurrentSpriteSpec();		// hàm này sẽ gọi nextFrame() trước khi kết thúc. goi truoc ham render cua GameObject
		void reverseAnimation(); // reverse animation order
		AnimationSpec();
		~AnimationSpec();
	};
}
#endif // !_ANIMATION_SPEC_H_




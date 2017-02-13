#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include "Texture.h"
#include "AnimationSpec.h"

namespace s_framework{
	class Animation
	{
	private:
		// texture chứa tất cả frame của 1 animation của 1 đối tượng. Animation chạy và nhảy có thể nằm ở 
		// 2 texture khác nhau. Xét đến trường hợp chơi nhiều màn.
		Texture* m_texture; 

		AnimationSpec* m_animationSpec;
		int m_index;							// current index của m_spriteSpecs
		int m_objectType;						// loại đối tượng
		int m_sate;								// trạng thái của đối tượng.

		/*      method         */
		void nextFrame();						// cập nhật lại chỉ số của frame tiếp theo


	public:
		Animation(Texture texture, int objectType, int state);
		Animation();
		~Animation();

		void setState(int state);				// thay đổi state của đối tượng. không cần setObject -> khi muốn thay đổi object thì 
												// dùng new để tạo đối tượng mới.
		SpriteSpec* getCurrentSpriteSpec();		// hàm này sẽ gọi nextFrame() trước khi kết thúc.

		Texture* getTexture();

	};

	
}
#endif // !_ANIMATION_H_




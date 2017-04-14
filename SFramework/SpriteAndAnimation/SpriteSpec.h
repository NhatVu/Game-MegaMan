#ifndef _SPRITE_SPEC_H_
#define _SPRITE_SPEC_H_

namespace s_framework{
	class SpriteSpec
	{

	private:
		float x; // tọa độ left trong image source
		float y; // tọa độ top trong image source
		float height; // chiều cao của sprite
		float width; // độ rộng của sprite
	public:
		SpriteSpec();
		~SpriteSpec();

		float getX();
		void setX(float);

		float getY();
		void setY(float);

		float getHeight();
		void setHeight(float);

		float getWidth();
		void setWidth(float);


	};
}

#endif // !_SPRITE_SPEC_H_




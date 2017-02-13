#ifndef _SPRITE_SPEC_H_
#define _SPRITE_SPEC_H_

namespace s_framework{
	class SpriteSpec
	{

	private:
		int x; // tọa độ left trong image source
		int y; // tọa độ top trong image source
		int height; // chiều cao của sprite
		int width; // độ rộng của sprite
	public:
		SpriteSpec();
		~SpriteSpec();

		int getX();
		void setX(int);

		int getY();
		void setY(int);

		int getHeight();
		void setHeight(int);

		int getWidth();
		void setWidth(int);


	};
}

#endif // !_SPRITE_SPEC_H_




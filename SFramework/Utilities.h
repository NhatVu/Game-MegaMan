#ifndef _UTILITIES_H_
#define _UTILITIES_H_


namespace s_framework{

	// vẽ ở tâm -> POINT là tâm hình
	struct FPOINT
	{
		float x;
		float y;

		FPOINT(){

		}

		FPOINT(float _x, float _y){
			x = _x;
			y = _y;
		}

		FPOINT operator - (const FPOINT& param)const
		{
			FPOINT result;
			result.x = x - param.x;
			result.y = y - param.y;
			return result;
		}

		FPOINT operator + (const FPOINT& param)const
		{
			FPOINT result;
			result.x = x + param.x;
			result.y = y + param.y;
			return result;
		}

		
	};

	struct BOX {
		float x;
		float y;
		float width;
		float height;
		float vx;
		float vy;

		BOX(){

		}

		BOX(float x, float y, float width, float height){
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
		}

		BOX(float x, float y, float width, float height, float vx, float vy){
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
			this->vx = vx;
		}

		BOX(float vx, float vy){
			this->vx = vx;
			this->vy = vy;
		}
	};
	
}

#endif // _UTILITIES_H_

#ifndef _UTILITIES_H_
#define _UTILITIES_H_

#define GRAVITATIONAL_ACCELERATION -0.005f

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
			this->vy = vy;
		}

		BOX(float vx, float vy){
			this->vx = vx;
			this->vy = vy;
		}
	};
	
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
}

#endif // _UTILITIES_H_

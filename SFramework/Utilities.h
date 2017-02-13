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
	
}

#endif // _UTILITIES_H_

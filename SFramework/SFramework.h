#ifndef _S_FRAMEWORK_H_
#define _S_FRAMEWORK_H_
#include <d3d9.h>
#include <d3dx9.h>
//#include "Animation.h"
#include "Texture.h"

#define USING_S_FRAMEWORK using namespace s_framework
#define SAFE_DELETE(p) { if(p != NULL) delete p; p = NULL; }
#define FPS 60

namespace s_framework
{
	class SFramework
	{
	private:
		static SFramework *m_instance;
		LPDIRECT3D9 m_d3d = NULL;
		LPDIRECT3DDEVICE9 m_d3ddev = NULL;
		LPDIRECT3DSURFACE9 m_backBuffer = NULL;

	private:
		SFramework();
		~SFramework();
		
	public:
		static SFramework* getInstance();
		
		/*-----------------------------------------------------
		 * CLASS LOGICS
		 *----------------------------------------------------*/
		int init(HWND hwnd);
		void loop();
		void update(float delta);
		void render();
		int release();
		void run();

		/*-----------------------------------------------------
		 * GETTERS AND SETTERS
		 *---------------------------------------------------*/
		LPDIRECT3D9 getDirect3D();
		LPDIRECT3DDEVICE9 getDirect3DDevice();

	};
}
#endif // !_NS_FRAMEWORK_

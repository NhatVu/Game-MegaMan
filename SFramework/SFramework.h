#ifndef _S_FRAMEWORK_H_
#define _S_FRAMEWORK_H_
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
//#include "Animation.h"
#include "Texture.h"
//#include "DirectxInput.h"
#include "Sprite.h"
#include <list>

#define USING_S_FRAMEWORK using namespace s_framework
#define SAFE_DELETE(p) { if(p != NULL) delete p; p = NULL; }
#define FPS 30
#define KEYBOARD_BUFFER_SIZE 1024
#define KEY_DOWN(code) ( IsKeyDown(code) )

namespace s_framework
{
	class SFramework
	{
	private:
		static SFramework *m_instance;
		LPDIRECT3D9 m_d3d = NULL;
		LPDIRECT3DDEVICE9 m_d3ddev = NULL;
		LPDIRECT3DSURFACE9 m_backBuffer = NULL;

		//// Directx input
	
		std::list<Sprite*> list_object_input;


		LPDIRECTINPUT8       _di;		// The DirectInput object         
		LPDIRECTINPUTDEVICE8 _Keyboard;	// The keyboard device 

		BYTE  _KeyStates[256];			// DirectInput keyboard state buffer 

		// Buffered keyboard data
		DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE];

	private:
		SFramework();
		~SFramework();
		
	public:
		static SFramework* getInstance();
		
		/*-----------------------------------------------------
		 * CLASS LOGICS
		 *----------------------------------------------------*/
		int initDirectX(HWND hwnd);

		void loop(HWND hwnd);
		void update(float delta);
		void render();
		int release();
		void run();

		///*-------------------------------------------------
		// * DIRECTX INPUT
		// *--------------------------------------------------*/
		void attachInputObect(Sprite* object);
		void detachInputObject(Sprite* object);

		void initKeyboard(HINSTANCE hInstance, HWND hWnd);
		void processKeyBoard(HWND hWnd);
		int isKeyDown(int KeyCode);
		virtual void processInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);

		virtual void onKeyDown(int KeyCode);
		virtual void onKeyUp(int KeyCode);

		/*-----------------------------------------------------
		 * GETTERS AND SETTERS
		 *---------------------------------------------------*/
		LPDIRECT3D9 getDirect3D();
		LPDIRECT3DDEVICE9 getDirect3DDevice();

	};
}
#endif // !_NS_FRAMEWORK_

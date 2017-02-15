#ifndef _DIRECTX_INPUT_H
#define _DIRECTX_INPUT_H

#include <d3d9.h>
#include <dinput.h>

#define KEYBOARD_BUFFER_SIZE	1024

namespace s_framework{
	class DirectxInput
	{
	public:
		DirectxInput();
		~DirectxInput();
	private: 
		static DirectxInput* m_instance;
		LPDIRECTINPUT8       _di;		// The DirectInput object         
		LPDIRECTINPUTDEVICE8 _Keyboard;	// The keyboard device 

		BYTE  _KeyStates[256];			// DirectInput keyboard state buffer 

		// Buffered keyboard data
		DIDEVICEOBJECTDATA _KeyEvents[KEYBOARD_BUFFER_SIZE];
	public: 
		static DirectxInput* getInstance();
		void initKeyboard(HINSTANCE hInstance,HWND hWnd);
		void processKeyBoard(HWND hWnd);
		int isKeyDown(int KeyCode);
		virtual void processInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);

		virtual void onKeyDown(int KeyCode);
		virtual void onKeyUp(int KeyCode);
	};

}
#endif // !_DIRECTX_INPUT_H

#include "SFramework.h"
#include "GameTime.h"
#include "Director.h"
#include "Node.h"

using namespace s_framework;

SFramework *SFramework::m_instance = NULL;

#define BACKGROUND_COLOR D3DCOLOR_XRGB(242, 237, 237)

SFramework::SFramework() 
{
}

SFramework::~SFramework()
{

}

SFramework* SFramework::getInstance(){
	if (m_instance == NULL)
		m_instance = new SFramework();
	return m_instance;
}

LPDIRECT3D9 SFramework::getDirect3D(){
	return m_d3d;
}

LPDIRECT3DDEVICE9 SFramework::getDirect3DDevice()
{
	return m_d3ddev;
}

int SFramework::initDirectX(HWND hwnd)
{
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_d3d) return 0;

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;

	m_d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hwnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_d3ddev);

	if (m_d3ddev == NULL) {
		MessageBox(NULL, L"Failed to create device", L"Error", MB_OK);
		return 0;
	}

	m_d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &m_backBuffer);

	//int result =
	//	d3ddev->CreateOffscreenPlainSurface(
	//	250,					// width 				
	//	250,					// height
	//	D3DFMT_X8R8G8B8,		// format
	//	D3DPOOL_DEFAULT,		// where? (VRAM or RAM)
	//	&surface,
	//	NULL);

	//D3DXCreateSprite(d3ddev, &sprite_handler);
	//Kitty = new Texture(sprite_handler, "ImageResource\\kitty.bmp", 92, 60, 6, 3);

	/*drawText = new UserDrawText();
	drawText->Initialize(d3ddev);
	RECT tempt;
	SetRect(&tempt, 0, 0, 100, 40);
	drawText->setTextRect(tempt);
	drawText->setMessage("this is a simple text");*/
	
	// load resource, có thể ghi nguồn ra 1 file text rồi chỉnh trong đó.
	//Texture::getInstance()->init("Resource/texture.png", "Resource/texture.xml");
	//Animation::getInstance()->init("Resource/animation.xml");

	return 1;
}

int SFramework::release()
{
	SAFE_DELETE(m_instance);
	return 1;
}


void SFramework::run(){
	m_d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, BACKGROUND_COLOR, 1.0f, 0);
	if (m_d3ddev->BeginScene()) {
		m_d3ddev->ColorFill(m_backBuffer, NULL, BACKGROUND_COLOR);

		// Render
		render();

		m_d3ddev->EndScene();
	}

	m_d3ddev->Present(NULL, NULL, NULL, NULL);
}

void SFramework::loop(HWND hwnd)
{
	//DWORD frame_start = GetTickCount();
	GameTime::getInstance()->setStartTime();
	//DWORD count_per_frame = 1000 / FPS;

	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// Do our game stuff here
		//DWORD now = GetTickCount();
		GameTime::getInstance()->setEndTime();

		if (GameTime::getInstance()->getDeltaTime() > GameTime::getInstance()->getTimePerFrame())
		{
			GameTime::getInstance()->setStartTime();
			// run game
			run();
		}		
		else
		{
			int sleepTime = GameTime::getInstance()->getTimeSleep();
			if (sleepTime > 0)
				Sleep(sleepTime);
		}

		// process input
		DirectxInput::getInstance()->processKeyBoard(hwnd);
		DirectxInput::getInstance()->processInput(m_d3ddev, GameTime::getInstance()->getDeltaTime());
	}
}

void SFramework::update(float delta)
{

}

void SFramework::render()
{
	Director::getInstance()->render();
}

//
//void SFramework::initKeyboard(HINSTANCE hInstance, HWND hWnd)
//{
//	HRESULT
//		hr = DirectInput8Create
//		(
//		hInstance,
//		DIRECTINPUT_VERSION,
//		IID_IDirectInput8, (VOID**)&_di, NULL
//		);
//
//	// TO-DO: put in exception handling
//	if (hr != DI_OK) return;
//
//
//	hr = _di->CreateDevice(GUID_SysKeyboard, &_Keyboard, NULL);
//
//	// TO-DO: put in exception handling
//	if (hr != DI_OK) return;
//
//
//	// Set the data format to "keyboard format" - a predefined data format 
//	//
//	// A data format specifies which controls on a device we
//	// are interested in, and how they should be reported.
//	//
//	// This tells DirectInput that we will be passing an array
//	// of 256 bytes to IDirectInputDevice::GetDeviceState.
//
//	hr = _Keyboard->SetDataFormat(&c_dfDIKeyboard);
//
//	//trace(L"SetDataFormat for keyboard successfully");
//
//	hr = _Keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
//
//	//trace(L"SetCooperativeLevel for keyboard successfully");
//
//	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
//	//
//	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
//	// If you want to read buffered data, you need to set a nonzero
//	// buffer size.
//	//
//	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
//	//
//	// The buffer size is a DWORD property associated with the device.
//	DIPROPDWORD dipdw;
//
//	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
//	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
//	dipdw.diph.dwObj = 0;
//	dipdw.diph.dwHow = DIPH_DEVICE;
//	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size
//
//	//trace(L"SetProperty for keyboard successfully");
//
//	hr = _Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
//	if (hr != DI_OK) return;
//
//	hr = _Keyboard->Acquire();
//	if (hr != DI_OK) return;
//
//	//trace(L"Keyboard has been acquired successfully");
//}
//
//void SFramework::processKeyBoard(HWND hWnd)
//{
//	// Collect all key states first
//	_Keyboard->GetDeviceState(sizeof(_KeyStates), _KeyStates);
//
//	if (isKeyDown(DIK_ESCAPE))
//	{
//		PostMessage(hWnd, WM_QUIT, 0, 0);
//	}
//
//	// Collect all buffered events
//	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
//	HRESULT hr = _Keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);
//
//	// Scan through all data, check if the key is pressed or released
//	for (DWORD i = 0; i < dwElements; i++)
//	{
//		int KeyCode = _KeyEvents[i].dwOfs;
//		int KeyState = _KeyEvents[i].dwData;
//		if ((KeyState & 0x80) > 0)
//			onKeyDown(KeyCode);
//		else
//			onKeyUp(KeyCode);
//	}
//}
//
//int SFramework::isKeyDown(int KeyCode)
//{
//	return (_KeyStates[KeyCode] & 0x80) > 0;
//}
//
//void SFramework::onKeyUp(int KeyCode) { }
//void SFramework::onKeyDown(int KeyCode) { }
//void SFramework::processInput(LPDIRECT3DDEVICE9 d3ddv, int Delta){}
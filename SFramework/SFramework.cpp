#include "SFramework.h"
#include "GameTime.h"
#include "Director.h"
#include "Node.h"
#include "Trace.h"
#include <algorithm>


using namespace s_framework;
using namespace std;

SFramework *SFramework::m_instance = NULL;

#define BACKGROUND_COLOR D3DCOLOR_XRGB(242, 237, 237)

SFramework::SFramework()
{
}

SFramework::~SFramework()
{
	if (m_d3ddev != NULL) m_d3ddev->Release();
	if (m_d3d != NULL) m_d3d->Release();

	if (_Keyboard)
	{
		_Keyboard->Unacquire();
		_Keyboard->Release();
	}

	if (_di) _di->Release();

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

// call in game loop
void SFramework::run(HWND hwnd){
	m_d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, BACKGROUND_COLOR, 1.0f, 0);
	if (m_d3ddev->BeginScene()) {
		m_d3ddev->ColorFill(m_backBuffer, NULL, BACKGROUND_COLOR);
		// update: collision and update position

		update(1.0f);

		// Render
		render();

		m_d3ddev->EndScene();
	}

	m_d3ddev->Present(NULL, NULL, NULL, NULL);

	// process keywboard
	processKeyBoard(hwnd);

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
		GameTime::getInstance()->setCurrentTime(); // tính toán lại biến mDeltaTime
		// nếu thời gian delta > TimePerFrame => setStartTime(set lại biến mStartTime)
		if (GameTime::getInstance()->getDeltaTime() > GameTime::getInstance()->getTimePerFrame())
		{
			//trace("delta time in sFramework " + std::to_string(GameTime::getInstance()->getDeltaTime()));
			GameTime::getInstance()->setStartTime();
			// run game
			run(hwnd);
		}
		else
		{
			int sleepTime = GameTime::getInstance()->getTimeSleep();
			if (sleepTime > 0)
				Sleep(sleepTime);
		}
	}
}

void SFramework::update(float delta)
{
	vector<GameObject*> mListObject = ((Scene*)Director::getInstance()->getScene())->getListGameObject();
	for (int i = 0; i < mListObject.size(); i++){
		if (mListObject[i]->getType() != 0)
		{
			for (int j = 0; j < mListObject.size(); j++)
			if (i != j)
				mListObject[i]->onCollision(mListObject[j]);
		}
	}
}

void SFramework::render()
{
	Director::getInstance()->render();
}

void SFramework::attachInputObect(GameObject* object){
	list_object_input.push_back(object);
}

void SFramework::detachInputObject(GameObject* object){
	list_object_input.erase(std::remove(list_object_input.begin(), list_object_input.end(), object), list_object_input.end());
}

void SFramework::initKeyboard(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT
		hr = DirectInput8Create
		(
		hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8, (VOID**)&_di, NULL
		);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;


	hr = _di->CreateDevice(GUID_SysKeyboard, &_Keyboard, NULL);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;


	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = _Keyboard->SetDataFormat(&c_dfDIKeyboard);

	//trace(L"SetDataFormat for keyboard successfully");

	hr = _Keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);

	//trace(L"SetCooperativeLevel for keyboard successfully");

	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	trace("SetProperty for keyboard successfully");

	hr = _Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return;

	hr = _Keyboard->Acquire();
	if (hr != DI_OK) return;

	trace("Keyboard has been acquired successfully");
}

// processKeyBoard call in Game loop. 
// It calls onKeyUp, onKeyDown. Two method with call onKeyUp, onKeyDown for each
// sprite that in list_object sprites
void SFramework::processKeyBoard(HWND hWnd)
{
	// Collect all key states first
	HRESULT result = _Keyboard->GetDeviceState(sizeof(_KeyStates), _KeyStates);

	if (FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if ((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			_Keyboard->Acquire();
		}
		else
		{
			return;
		}
	}

	if (isKeyDown(DIK_ESCAPE))
	{
		PostMessage(hWnd, WM_QUIT, 0, 0);
	}

	if (isKeyDown(DIK_RIGHT)){
		trace("RIght key down in device state");
		int a = 0;
	}

	processKeyState(_KeyStates);

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = _Keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);

	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0){
			if (KeyCode == DIK_RIGHT)
				trace("RIGHT keydown in device Data");
			onKeyDown(KeyCode);
		}
		else
			onKeyUp(KeyCode);
	}
	//if (FAILED(hr))
	//{
	//	// If the keyboard lost focus or was not acquired then try to get control back.
	//	if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED))
	//	{
	//		_Keyboard->Acquire();
	//	}
	//	else
	//	{
	//		return;
	//	}
	//}
	//ZeroMemory(&_KeyEvents, sizeof(_KeyEvents));
}

int SFramework::isKeyDown(int KeyCode)
{
	return (_KeyStates[KeyCode] & 0x80) > 0;
}

void SFramework::onKeyUp(int KeyCode) {
	std::list<GameObject*>::const_iterator iterator;
	for (iterator = list_object_input.begin(); iterator != list_object_input.end(); ++iterator) {
		if (*iterator != 0){
			GameObject* test = (*iterator);
			test->onKeyUp(KeyCode);
		}
	}
}

void SFramework::onKeyDown(int KeyCode) {
	std::list<GameObject*>::const_iterator iterator;
	for (iterator = list_object_input.begin(); iterator != list_object_input.end(); ++iterator) {
		if (*iterator != 0){
			GameObject* test = (*iterator);
			test->onKeyDown(KeyCode);
		}
	}
}

void SFramework::processKeyState(BYTE *keyState){
	std::list<GameObject*>::const_iterator iterator;
	for (iterator = list_object_input.begin(); iterator != list_object_input.end(); ++iterator) {
		if (*iterator != 0){
			GameObject* test = (*iterator);
			test->processKeyState(keyState);
		}
	}
}

#include "DirectxInput.h"

using namespace s_framework;

DirectxInput* DirectxInput::m_instance = NULL;

DirectxInput::DirectxInput()
{
}


DirectxInput::~DirectxInput()
{
}

DirectxInput* DirectxInput::getInstance(){
	if (m_instance == NULL)
		return new DirectxInput();
	return m_instance;
}

void DirectxInput::initKeyboard(HINSTANCE hInstance, HWND hWnd)
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

	//trace(L"SetProperty for keyboard successfully");

	hr = _Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return;

	hr = _Keyboard->Acquire();
	if (hr != DI_OK) return;

	//trace(L"Keyboard has been acquired successfully");
}

void DirectxInput::processKeyBoard(HWND hWnd)
{
	// Collect all key states first, save to _KeyStates
	_Keyboard->GetDeviceState(sizeof(_KeyStates), _KeyStates);

	if (isKeyDown(DIK_ESCAPE))
	{
		PostMessage(hWnd, WM_QUIT, 0, 0);
	}

	// Collect all buffered events
	DWORD dwElements = KEYBOARD_BUFFER_SIZE;
	HRESULT hr = _Keyboard->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0);

	// Scan through all data, check if the key is pressed or released
	for (DWORD i = 0; i < dwElements; i++)
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;
		if ((KeyState & 0x80) > 0)
			onKeyDown(KeyCode);
		else
			onKeyUp(KeyCode);
	}
}

int DirectxInput::isKeyDown(int KeyCode)
{
	return (_KeyStates[KeyCode] & 0x80) > 0;
}

void DirectxInput::onKeyUp(int KeyCode) { }
void DirectxInput::onKeyDown(int KeyCode) { }
void DirectxInput::processInput(LPDIRECT3DDEVICE9 d3ddv, int Delta){}
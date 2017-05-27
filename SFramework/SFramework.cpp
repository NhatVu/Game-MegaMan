#include "SFramework.h"
#include "GameTime.h"
#include "Director.h"
#include "Node.h"
#include "Trace.h"
#include <algorithm>
#include <list>
#include <map>
#include "Map\ObjectManager.h"
#include "Camera\ViewPort.h"
#include "../MegaMan/MegaManUtilities.h"
#include "Collision.h"
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

		processKeyBoard(hwnd);
		
		update(1.0f);

		// Render
		render();
		// update postion before detect collision
		map<int, GameObject*> mapActiveObject = ObjectManager::getInstance()->getActiveObject();
		for (map<int, GameObject*>::iterator it = mapActiveObject.begin(); it != mapActiveObject.end(); ++it) {
			it->second->updatePosition();
		}
		
		m_d3ddev->EndScene();
	}

	m_d3ddev->Present(NULL, NULL, NULL, NULL);

	// process keywboard

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
			/*
			// FPS at that specific frame would be 1.0/dt assuming time is in seconds
			// Normally you get the time in microseconds or at least milliseconds
			//   so it would be 1.0/(dt*1e6) or 1.0/(dt*1e4)
			*/
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
	// trước khi xử lý va chạm, ta chạy quadtree để lấy đối tượng có khả năng va chạm
	ObjectManager *objectManager = ObjectManager::getInstance();
	objectManager->processQuadTreeAndViewport(ViewPort::getInstance()->getPosition());
	map<int, GameObject*> mapQuadtreeBackground = objectManager->getQuadtreeBackground();
	map<int, GameObject*> mapActiveObject = objectManager->getActiveObject();

	// clear old scene
	delete Director::getInstance()->getScene();
	Scene* newScene = new Scene();
	for (map<int, GameObject*>::iterator it = mapQuadtreeBackground.begin(); it != mapQuadtreeBackground.end(); ++it) {
		newScene->addChild(it->second);
	}
	vector<GameObject*> mListObject;
	for (map<int, GameObject*>::iterator it = mapActiveObject.begin(); it != mapActiveObject.end(); ++it) {
		GameObject* tmp = it->second;
		// object inactive => ko xét va chạm, không vẽ
		if (tmp->getIsInactive())
			continue;
		mListObject.push_back(it->second);

		if (tmp->getType() == ECharacter::STATIC || tmp->getType() == ECharacter::LADDER)
			continue;
		if (tmp->getType() == ECharacter::KAMADOMA){
			int a = 5;
		}
		newScene->addChild(tmp);
	}	
	Director::getInstance()->setScene(newScene);
	struct {
		bool operator()(GameObject* a, GameObject* b) const
		{
			return a->getType() > b->getType();
		}
	} customGreater;
	std::sort(mListObject.begin(), mListObject.end(), customGreater);
	

	for (int i = 0; i < mListObject.size(); i++){
		if (mListObject[i]->getType() != ECharacter::STATIC && mListObject[i]->getType() != ECharacter::LADDER)
		{
			for (int j = 0; j < mListObject.size(); j++){
				if (mListObject[j]->getType() != 0 && i != j){
					mListObject[i]->calculateCollisionBox();
					D3DXVECTOR2 collisionVector(0.0f, 0.0f);
					float collisionTime = Collision::CheckCollision(mListObject[i], mListObject[j], collisionVector);
					mListObject[i]->onCollision(mListObject[j], collisionTime, collisionVector);
					collisionVector.x *= -1;
					collisionVector.y *= -1;
					mListObject[j]->onCollision(mListObject[i], collisionTime, collisionVector);
					if (mListObject[j]->getType() == 1){
						int x = 5;
					}
					if (collisionTime > 0.0f && collisionTime <= 1.0f){
						break;
					}
				}
			}

		}
	}

	for (int i = 0; i < mListObject.size(); i++){
		if (mListObject[i]->getType() != 0)
		{
			for (int j = 0; j < mListObject.size(); j++){
				if (mListObject[j]->getType() == 0 && i != j){
					mListObject[i]->calculateCollisionBox();
					D3DXVECTOR2 collisionVector;
					float collisionTime = Collision::CheckCollision(mListObject[i], mListObject[j], collisionVector);
					mListObject[i]->onCollision(mListObject[j], collisionTime, collisionVector);
					collisionVector.x *= -1;
					collisionVector.y *= -1;
					//mListObject[j]->onCollision(mListObject[i], collisionTime, collisionVector);
					if (mListObject[i]->getTimeCollision() > 0.0f && mListObject[i]->getTimeCollision() <= 1.0f){
					}
				}
			}

		}
	}

	// update viewport position 
	ViewPort::getInstance()->updateViewportNextFrame();
	//// update postion before detect collision
	//for (int i = 0; i < mListObject.size(); i++){
	//	mListObject[i]->updatePosition();
	//}

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

void s_framework::SFramework::detectCollision(list<GameObject*> game_objects)
{
	Quadtree* quadtree = CreateQuadTree(game_objects);

	list<GameObject*> return_objects_list;

	for (list<GameObject*>::iterator i = game_objects.begin(); i != game_objects.end(); i++)
	{
		//Get all objects that can collide with current entity
		quadtree->Retrieve(return_objects_list, *i);

		for (auto x = return_objects_list.begin(); x != return_objects_list.end(); x++)
		{
			GameObject* a = *i;
			GameObject* b = *x;
			//if (a->onCollision(b) == true)
			//{
				///
			//}
		}

		return_objects_list.clear();
	}

	quadtree->Release();
}

Quadtree* s_framework::SFramework::CreateQuadTree(list<GameObject*> game_objects)
{
	Quadtree* quadtree = new Quadtree(1, BOX(0, 0, 800, 600));


	for (auto i = game_objects.begin(); i != game_objects.end(); i++)
		quadtree->Insert(*i);
	return quadtree;
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

	//trace("SetProperty for keyboard successfully");

	hr = _Keyboard->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (hr != DI_OK) return;

	hr = _Keyboard->Acquire();
	if (hr != DI_OK) return;

	//trace("Keyboard has been acquired successfully");
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
			onKeyDown(KeyCode);
		}
		else
			onKeyUp(KeyCode);
	}

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

#ifndef _WinMain_H_
#define _WinMain_H_

#include <Windows.h>
#include "../SFramework/SFramework.h"
#include "../SFramework/GameTime.h"
#include "../SFramework/Scene.h"
#include "../SFramework/Layer.h"
#include "../SFramework/GameObject.h"
#include "../SFramework/Director.h"
#include "../SFramework/SpriteAndAnimation/SpriteSpec.h"
#include "../SFramework/Camera/ViewPort.h"
#include "../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../SFramework/Map/GameMap.h"
#include "../SFramework/Map/ObjectManager.h"
#include "../SFramework/SpriteAndAnimation/TextureManager.h"
#include "MegaManUtilities.h"
#include "GameObject/MegaMan.h"
#include "Map/MapBombMan.h"

#define APP_CLASS L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Mega Man"



USING_S_FRAMEWORK;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

HWND hwnd;

bool initializeWindow(HINSTANCE hInstance){

	WNDCLASSEX wndClass = { 0 };

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;

	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = APP_CLASS;

	if (!RegisterClassEx(&wndClass))
		return -1;

	hwnd = CreateWindow(APP_CLASS,
		MAIN_WINDOW_TITLE,
		WS_OVERLAPPEDWINDOW,
		//WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hwnd)
		return FALSE;

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	return TRUE;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPWSTR cmdLine, int cmdShow)
{
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(cmdLine);

	if (!initializeWindow(hInstance))
		return FALSE;

	// install directx
	if (!SFramework::getInstance()->initDirectX(hwnd))
		return FALSE;

	// install directx input, keyboard
	SFramework::getInstance()->initKeyboard(hInstance, hwnd);

	// Install Gametime
	GameTime::getInstance();


	// load hình
	//Texture* texture = new Texture();
	//texture->init("Resources/texture.png", "Resources/texture.xml");

	//AnimationManager::getInstance()->parseAnimationXML("Resource/animation.xml");
	AnimationManager::getInstance()->parseAnimationJSON("Resources/animation.json");

	FPOINT p;
	
	// create object
	GameObject* megaMan = new MegaMan();
	megaMan->setTexture(TextureManager::getInstance()->getObjectTexture());
	megaMan->setObjectID(0);
	((MegaMan*)megaMan)->setState(EState::IDLE);
	// vị trí của mega man trong world
	ObjectManager::getInstance()->setMegaMan(megaMan);
	p.x = 130;
	//p.x = 52 * 32; // test change viewport state
	p.y = 200;
	megaMan->setPostion(p); // bắt buộc phải là top-left của vật. 
	megaMan->setInitPosition(p);
	// attach megaman object in order to receive event when keyboard press
	SFramework::getInstance()->attachInputObect(megaMan);

	// map
	MapBombMan* mapBombMan = new MapBombMan("Resources/map.tmx", megaMan);
	mapBombMan->init();

	/*
	* Kết thúc giai đoạn tạo map và các đối tượng trong game. Câu hỏi đặt ra là khi chuyển map từ màn 1 sang màn 2, sẽ khơi tạo map màn 2 mở đâu ?
	*/
	// game loop
	SFramework::getInstance()->loop(hwnd);

	//GameRelease();

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}
#endif // !_WinMain_H_
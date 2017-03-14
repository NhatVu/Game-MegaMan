#ifndef _WinMain_H_
#define _WinMain_H_

#include <Windows.h>
#include "../SFramework/SFramework.h"
#include "../SFramework/GameTime.h"
#include "../SFramework/Scene.h"
#include "../SFramework/Layer.h"
#include "../SFramework/Sprite.h"
#include "../SFramework/Director.h"
#include "../SFramework/Texture.h"
#include "../SFramework/SpriteSpec.h"
#include "../SFramework/ViewPort.h"
#include "../SFramework/ResourceManager.h"
#include "../SFramework/GameMap.h"

#include "MegaManUtilities.h"
#include "MegaMan.h"

#define APP_CLASS L"SampleWindow"
#define MAIN_WINDOW_TITLE L"Mega Man"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

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
	//DirectxInput::getInstance()->initKeyboard(hInstance, hwnd);
	SFramework::getInstance()->initKeyboard(hInstance, hwnd);

	
	GameTime::getInstance();

	// thiết lập ma trận transform
	//ViewPort::getInstance()->setPosition(FPOINT(20, 20));

	// load hình
	Texture* texture = new Texture();
	texture->init("Resources/texture.png", "Resources/texture.xml");

	//ResourceManager::getInstance()->parseAnimationXML("Resource/animation.xml");
	ResourceManager::getInstance()->parseAnimationJSON(texture,"Resources/animation.json");

	// create layer
	//s_framework::Layer* layer = new s_framework::Layer();
	//layer->setHeight(SCREEN_HEIGHT );
	//layer->setWidth(SCREEN_WIDTH );
	//FPOINT p;/*
	//p.x = SCREEN_WIDTH * 3;
	//p.y = SCREEN_HEIGHT * 2;*/
	//p.x = 0;
	//p.y = 0;
	////scene->setPostion(FPOINT((float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2));

	//layer->setPostion(p);

	// create scene, and add layer to scene
	Scene* scene = new Scene();
	scene->setHeight(SCREEN_HEIGHT );
	scene->setWidth(SCREEN_WIDTH );
	//scene->setPostion(FPOINT((float)SCREEN_WIDTH *2, (float)SCREEN_HEIGHT *2));
	scene->setPostion(FPOINT(0, 0));

	//scene->addChild(layer);

	// set scene to director to draw
	Director::getInstance()->setScene(scene);	
	
	/*p.x = p.x + 100;
	p.y = p.y + 200;*/
	FPOINT p;
	p.x = -100;
	p.y = 300;
	ViewPort::getInstance()->setPosition(p); // vị trí left-top của viewport

	// create object
	Sprite* megaMan = new MegaMan();
	megaMan->setTexture(texture);
	((MegaMan*)megaMan)->changeAnimation(ECharacter::SMALL_MARIO, EState::MOVE);
	 //megaMan->setAnimationSpec(ECharacter::BIG_MARIO, EState::DIE)
	//Sprite* sprite = new Sprite(texture, texture->getSpriteSpecById(19));
	p.x = 200;
	p.y = 00;
	megaMan->setPostion(p);

	

	// map
	GameMap* map = new GameMap("Resources/map.tmx");
	//map->Draw();
	vector<Node*> mapNode = map->getScene();
	for (int i = 0; i < mapNode.size(); i++){
		scene->addChild(mapNode[i]);
	}
	scene->addChild(megaMan);

	// attach megaman object in order to receive event when keyboard press
	SFramework::getInstance()->attachInputObect(megaMan);
	//((Subject*)DirectxInput::getInstance())->Attach((IObserver*)megaMan);
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
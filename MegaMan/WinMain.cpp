#ifndef _WinMain_H_
#define _WinMain_H_

#include <Windows.h>
#include "../SFramework/SFramework.h"
#include "../SFramework/GameTime.h"
#include "../SFramework/Scene.h"
#include "../SFramework/Layer.h"
#include "../SFramework/GameObject.h"
#include "../SFramework/Director.h"
#include "../SFramework/SpriteAndAnimation/Texture.h"
#include "../SFramework/SpriteAndAnimation/SpriteSpec.h"
#include "../SFramework/Camera/ViewPort.h"
#include "../SFramework/SpriteAndAnimation/AnimationManager.h"
#include "../SFramework/Map/GameMap.h"

#include "MegaManUtilities.h"
#include "GameObject/MegaMan.h"

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

	// Install Gametime
	GameTime::getInstance();


	// load hình
	Texture* texture = new Texture();
	texture->init("Resources/texture.png", "Resources/texture.xml");

	//AnimationManager::getInstance()->parseAnimationXML("Resource/animation.xml");
	AnimationManager::getInstance()->parseAnimationJSON(texture,"Resources/animation.json");

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
	scene->setPostion(FPOINT(0, 0));

	//scene->addChild(layer);

	// set scene to director to draw
	Director::getInstance()->setScene(scene);	
	
	/*p.x = p.x + 100;
	p.y = p.y + 200;*/
	FPOINT p;
	p.x = -00.0f;
	p.y = 224.0f;
	ViewPort::getInstance()->setPosition(p); // vị trí left-top của viewport trong thế giới.

	// create object
	GameObject* megaMan = new MegaMan();
	megaMan->setTexture(texture);
	((MegaMan*)megaMan)->setState(EState::IDLE);
	// vị trí của mega man trong world

	// va chạm top, từ trên xuống
	p.x = 100;
	p.y = 150; 

	// check va chạm bottom, từ dưới lên. nhớ chỉnh lại gravitational_acceleration
	p.x = 100;
	p.y = -150;

	// va chạm trái. chỉnh gia tốc trọng trường = 0
	p.x = 100;
	//p.y = 66; //mega man bottom trùng với ground top
	p.y = 100;
	megaMan->setPostion(p); // bắt buộc phải là top-left của vật. 

	

	// map
	GameMap* map = new GameMap("Resources/map.tmx", texture);
	//map->draw();
	vector<Node*> mapNode = map->getNodesBackground();
	for (int i = 0; i < mapNode.size(); i++){
		scene->addChild(mapNode[i]);
	}
	scene->addChild(megaMan);

	vector<GameObject*> mListObject = map->getListObject();
	megaMan->setType(2);
	scene->addGameObject(megaMan);
	scene->addGameObjects(mListObject);
	//for (int i = 0; i < mListObject.size(); i++)
	//	scene->addChild(mListObject[i]);


	//for (int i = 0; i < mListObject.size(); i++){
	//	if (mListObject[i]->getType() != 1)
	//	{
	//		for (int j = 0; j < mListObject.size() && i != j; j++)
	//			mListObject[i]->onCollision(mListObject[j]);
	//	}
	//}

	/*for (int i = 0; i < mListObject.size(); i++){

		printf("Object Position: (%03d, %03d)\n", mListObject[i]->getCollisionBox().x,
			mListObject[i]->getCollisionBox().y);
		printf("Object Size: (%03d, %03d)\n", mListObject[i]->getCollisionBox().width,
			mListObject[i]->getCollisionBox().height);
	}*/

	// attach megaman object in order to receive event when keyboard press
	SFramework::getInstance()->attachInputObect(megaMan);
	//((Subject*)DirectxInput::getInstance())->Attach((IObserver*)megaMan);

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
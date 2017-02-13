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

int SFramework::init(HWND hwnd)
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

void SFramework::loop()
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
			run();
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

}

void SFramework::render()
{
	Director::getInstance()->render();
}

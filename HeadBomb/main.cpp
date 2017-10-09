/// main.cpp
// あたまばくだん
// author syuk nishida
// 2014/09/23

/// Memory leak check
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

/// Includes
#include <Windows.h>
#include <snStudy.h>
#pragma comment(lib,"winmm.lib")
#include "Title.h"
#include "Game.h"
#include "Result.h"
#include "Input.h"

/// Macros
#define SCREEN_SIZE_W	(800)
#define SCREEN_SIZE_H	(600)
#define WINDOW_NAME		"あたまばくだん"

/// Global variable
DWORD	gFPSLastTime = timeGetTime();
DWORD	gExecLastTime = timeGetTime();
DWORD	gCurrentTime = timeGetTime();
DWORD	gFrameCount = 0;
int		gCountFPS = 0;

/// プロシージャ
// 引数　：ウィンドウハンドルとメッセージとパラメータ
// 戻り値：結果
// 2014/09/23
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	// Message branch
	switch (uMsg) {

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam) {
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;

	case WM_CLOSE:
		break;

	default:
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

/// エントリーポイント
// 引数　：インスタンスハンドルとコマンドライン引数
// 戻り値：結果
// 2014/09/23
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	// Leak check
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Variable daclaration
	MSG msg;
	WNDCLASSEX wcex = {
		sizeof(WNDCLASSEX),				// Struct size
		CS_CLASSDC,						// Window style
		WndProc,						// Window procedure function pointer
		0,
		0,
		hInstance,						// Instance handle
		NULL,							// Icon handle
		LoadCursor(NULL, IDC_ARROW),	// Mouse cursor handle
		(HBRUSH)(COLOR_WINDOW),			// Background color
		NULL,							// Menu name
		WINDOW_NAME,					// Window class name
		NULL							// Mini icon
	};

	// レンダリングマネージャ初期化
	snStudy::RenderingManager::Initalize(hInstance, nCmdShow, wcex, SCREEN_SIZE_W, SCREEN_SIZE_H, WINDOW_NAME);

	// インプット初期化
	DirectInputModuleInit(hInstance,snStudy::RenderingManager::GetPointer()->GetWindowHandle());
	DirectInputKeyboardInid();

	// ドローエレメント初期化
	snStudy::DrawElement::InitDecralation();

	/// ライト
	snStudy::Light::LightElement light;
	light.type = snStudy::Light::DIRECTIONAL;
	light.diffuse = snStudy::Color4f(1, 1, 1, 1);
	light.direction = snStudy::Vector3f(-0.5f, -1, 0.5f).Normal();
	snStudy::Light::AddLight(light);

	// シーン
	TitleScene* titleScene = TitleScene::Create();
	GameScene* gameScene = GameScene::Create();
	ResultScene* resultScene = ResultScene::Create();
	snStudy::SceneManager::Init(TITLE_NUM);

	/// Instantion game manager

	// Message loop
	for (;;){
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
			// If message is quit them break to loop
			if (msg.message == WM_QUIT) break;

			// If get to message them message handling
			else TranslateMessage(&msg), DispatchMessage(&msg);
		}
		else{
			snStudy::RenderingManager::Step();
		}
	}

	// シーン修了
	titleScene->Release();
	gameScene->Release();
	resultScene->Release();
	snStudy::SceneManager::Uninit();

	// ライト終了
	snStudy::Light::Release();

	// テクスチャ終了
	snStudy::TextureManager::Release();

	// インプット修了
	DirectInputModuleUninit();

	// レンダラ終了
	snStudy::RenderingManager::Finalize();

	// Post processing to window
	UnregisterClass(WINDOW_NAME, hInstance);

	return (int)msg.wParam;
}
//=EOF=
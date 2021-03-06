#include "WinApp.h"

LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_DESTROY://ウィンドウ破棄
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

const wchar_t WinApp::windowClassName[] = L"OASOBI";
void WinApp::CreateMainWindow()
{
	//ウィンドウ生成
	//ウィンドウクラスの設定
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;//ウィンドウプロシージャを設定
	w.lpszClassName = windowClassName;//ウィンドウクラス名
	w.hInstance = GetModuleHandle(nullptr);//ウィンドウハンドル
	w.hCursor = LoadCursor(NULL, IDC_ARROW);//カーソル設定

	//ウィンドウクラスをOSに登録
	RegisterClassEx(&w);
	//ウィンドウサイズ(X,Y,横幅,縦幅)
	RECT wrc = { 0,0,window_width,window_height };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);//自動でサイズ補正

	//ウィンドウオブジェクトの生成
	hwnd = CreateWindow(w.lpszClassName,//クラス名
		windowClassName,							//タイトルバーの文字
		WS_OVERLAPPEDWINDOW,					//標準的なウィンドウスタイル
		CW_USEDEFAULT,							//表示X座標(OSに任せる)
		CW_USEDEFAULT,							//表示Y座標(OSに任せる)
		wrc.right - wrc.left,					//ウィンドウ横幅
		wrc.bottom - wrc.top,					//ウィンドウ縦幅
		nullptr,								//親ウィンドウハンドル
		nullptr,								//メニューハンドル
		w.hInstance,							//呼び出しアプリケーションハンドル
		nullptr);								//オプション

	//ウィンドウ表示
	ShowWindow(hwnd, SW_SHOW);
}

bool WinApp::ProcessMessage()
{
	MSG msg{};	// メッセージ

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){ // メッセージがある？
		TranslateMessage(&msg); // キー入力メッセージの処理
		DispatchMessage(&msg); // ウィンドウプロシージャにメッセージを送る
	}

	if (isQuit) { 
		PostQuitMessage(0);
		return true;
	}

	if (msg.message == WM_QUIT) { // 終了メッセージが来たらループを抜ける
		return true;
	}

	return false;
}

void WinApp::Terminatewindow()
{
	// ウィンドウクラスを登録解除
	UnregisterClass(w.lpszClassName, w.hInstance);
}

void WinApp::QuitApp()
{
	isQuit = true;
}
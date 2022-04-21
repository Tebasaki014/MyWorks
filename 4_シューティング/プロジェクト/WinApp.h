#pragma once
#include<Windows.h>
class WinApp
{
public:
	static const int window_width = 1280;//横幅
	static const int window_height = 720;//縦幅

	static const wchar_t windowClassName[];

	bool isQuit = false;

	void CreateMainWindow();
	bool ProcessMessage();
	void Terminatewindow();
	HWND GetHwnd() { return hwnd; }
	HINSTANCE GetInstance() { return w.hInstance; }
	void QuitApp();
private:
	////ウィンドウクラス
	WNDCLASSEX w{};
	////ウィンドウオブジェクト
	HWND hwnd = nullptr;
};
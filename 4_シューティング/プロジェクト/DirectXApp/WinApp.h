#pragma once
#include<Windows.h>
#include"Singleton.h"

class WinApp : public Singleton_Unique<WinApp>
{
private:
	//�V���O���g������
	friend Singleton_Unique<WinApp>;
	WinApp() = default;
public:
	static const int window_width = 1280;//����
	static const int window_height = 720;//�c��

	static const wchar_t windowClassName[];

	bool isQuit = false;

	void CreateMainWindow();
	bool ProcessMessage();
	void Terminatewindow();
	HWND GetHwnd() { return hwnd; }
	HINSTANCE GetHandleInstance() { return w.hInstance; }
	void QuitApp();
private:
	////�E�B���h�E�N���X
	WNDCLASSEX w{};
	////�E�B���h�E�I�u�W�F�N�g
	HWND hwnd = nullptr;
};
#include "WinApp.h"

LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_DESTROY://�E�B���h�E�j��
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

const wchar_t WinApp::windowClassName[] = L"OASOBI";
void WinApp::CreateMainWindow()
{
	//�E�B���h�E����
	//�E�B���h�E�N���X�̐ݒ�
	w.cbSize = sizeof(WNDCLASSEX);
	w.lpfnWndProc = (WNDPROC)WindowProc;//�E�B���h�E�v���V�[�W����ݒ�
	w.lpszClassName = windowClassName;//�E�B���h�E�N���X��
	w.hInstance = GetModuleHandle(nullptr);//�E�B���h�E�n���h��
	w.hCursor = LoadCursor(NULL, IDC_ARROW);//�J�[�\���ݒ�

	//�E�B���h�E�N���X��OS�ɓo�^
	RegisterClassEx(&w);
	//�E�B���h�E�T�C�Y(X,Y,����,�c��)
	RECT wrc = { 0,0,window_width,window_height };
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);//�����ŃT�C�Y�␳

	//�E�B���h�E�I�u�W�F�N�g�̐���
	hwnd = CreateWindow(w.lpszClassName,//�N���X��
		windowClassName,							//�^�C�g���o�[�̕���
		WS_OVERLAPPEDWINDOW,					//�W���I�ȃE�B���h�E�X�^�C��
		CW_USEDEFAULT,							//�\��X���W(OS�ɔC����)
		CW_USEDEFAULT,							//�\��Y���W(OS�ɔC����)
		wrc.right - wrc.left,					//�E�B���h�E����
		wrc.bottom - wrc.top,					//�E�B���h�E�c��
		nullptr,								//�e�E�B���h�E�n���h��
		nullptr,								//���j���[�n���h��
		w.hInstance,							//�Ăяo���A�v���P�[�V�����n���h��
		nullptr);								//�I�v�V����

	//�E�B���h�E�\��
	ShowWindow(hwnd, SW_SHOW);
}

bool WinApp::ProcessMessage()
{
	MSG msg{};	// ���b�Z�[�W

	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){ // ���b�Z�[�W������H
		TranslateMessage(&msg); // �L�[���̓��b�Z�[�W�̏���
		DispatchMessage(&msg); // �E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
	}

	if (isQuit) { 
		PostQuitMessage(0);
		return true;
	}

	if (msg.message == WM_QUIT) { // �I�����b�Z�[�W�������烋�[�v�𔲂���
		return true;
	}

	return false;
}

void WinApp::Terminatewindow()
{
	// �E�B���h�E�N���X��o�^����
	UnregisterClass(w.lpszClassName, w.hInstance);
}

void WinApp::QuitApp()
{
	isQuit = true;
}
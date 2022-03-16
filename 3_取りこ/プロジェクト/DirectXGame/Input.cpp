#include "Input.h"
#include <cassert>
#include "WinApp.h"

#pragma comment(lib, "dinput8.lib")

bool Input::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT result = S_FALSE;
	hwnnd = hwnd;

	// DirectInputオブジェクトの生成	
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// キーボードデバイスの生成	
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// マウス用にデバイスオブジェクトを作成
	result  = dinput->CreateDevice(GUID_SysMouse, &devmouse, NULL);
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	// 入力データ形式のセット
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// 入力データ形式のセット
	result = devmouse->SetDataFormat(&c_dfDIMouse);	// マウス用のデータ・フォーマットを設定
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	// 排他制御レベルのセット
	result = devkeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// モードを設定（フォアグラウンド＆非排他モード）
	result = devmouse->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	// デバイスの設定
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL;	// 相対値モードで設定（絶対値はDIPROPAXISMODE_ABS）

	result = devmouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	if (FAILED(result)) {
		// デバイスの設定に失敗
		return false;
	}

	return true;
}

void Input::Update()
{
	HRESULT result;

	result = devkeyboard->Acquire();	// キーボード動作開始
	result = devmouse->Acquire();		//マウス動作開始

	// 前回のキー入力を保存
	memcpy(keyPre, key, sizeof(key));
	premoustate = moustate;

	// キーの入力
	result = devkeyboard->GetDeviceState(sizeof(key), key);
	result = devmouse->GetDeviceState(sizeof(DIMOUSESTATE), &moustate);
}

bool Input::PushKey(BYTE keyNumber)
{
	// 異常な引数を検出
	assert(0 <= keyNumber && keyNumber <= 256);

	// 0でなければ押している
	if (key[keyNumber]) {
		return true;
	}

	// 押していない
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	// 異常な引数を検出
	assert(0 <= keyNumber && keyNumber <= 256);

	// 前回が0で、今回が0でなければトリガー
	if (!keyPre[keyNumber] && key[keyNumber]) {
		return true;
	}

	// トリガーでない
	return false;
}

bool Input::IsLeftClick()
{
	if (moustate.rgbButtons[0]) {
		return true;
	}
	else return false;
}

DirectX::XMFLOAT2 Input::GetMouseVelocity()
{
	return DirectX::XMFLOAT2((float)moustate.lX, (float)moustate.lY);
}

DirectX::XMFLOAT2 Input::GetMousePosition()
{
	POINT p;
	GetCursorPos(&p);
	ScreenToClient(hwnnd, &p);

	if (p.x < 0) { p.x = 0; }
	//if (p.x > ) { p.x = 0; }
	
	return DirectX::XMFLOAT2((float)p.x, (float)p.y);
}

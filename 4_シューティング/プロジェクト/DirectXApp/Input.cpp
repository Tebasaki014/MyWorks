#include "Input.h"
#include <cassert>

#pragma comment(lib, "dinput8.lib")

HRESULT Input::Initialize(HINSTANCE hInstance, HWND hwnd)
{
	HRESULT result = S_FALSE;

	// DirectInputオブジェクトの生成	
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&dinput, nullptr);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// キーボードデバイスの生成	
	result = dinput->CreateDevice(GUID_SysKeyboard, &devKeyboard, NULL);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// マウスデバイスの生成	
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// 入力データ形式のセット
	result = devKeyboard->SetDataFormat(&c_dfDIKeyboard); // 標準形式
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// 排他制御レベルのセット
	result = devKeyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// 入力データ形式のセット
	result = devMouse->SetDataFormat(&c_dfDIMouse2); // 標準形式
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	// 排他制御レベルのセット
	result = devMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(result)) {
		assert(0);
		return result;
	}

	return result;
}

void Input::Update()
{
	HRESULT result;

	{// キーボード
		result = devKeyboard->Acquire();	// キーボード動作開始

		// 前回のキー入力を保存
		memcpy(keyPre, key, sizeof(key));

		// キーの入力
		result = devKeyboard->GetDeviceState(sizeof(key), key);
	}

	{// マウス
		result = devMouse->Acquire();	// マウス動作開始

		// 前回の入力を保存
		mouseStatePre = mouseState;

		// マウスの入力
		result = devMouse->GetDeviceState(sizeof(mouseState), &mouseState);
	}
}

bool Input::IsKeyTouch(BYTE keyNumber)
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

bool Input::IsKeyDown(BYTE keyNumber)
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

bool Input::IsKeyUp(BYTE keyNumber)
{
	// 異常な引数を検出
	assert(0 <= keyNumber && keyNumber <= 256);

	// 前回が0 でなくて、今回が0であればトリガー
	if (keyPre[keyNumber] && !key[keyNumber]) {
		return true;
	}

	// トリガーでない
	return false;
}

bool Input::IsMousekeyTouch(int keyNumber)
{
	// 0でなければ押している
	if (mouseState.rgbButtons[keyNumber]) {
		return true;
	}

	// 押していない
	return false;
}

bool Input::IsMousekeyDown(int keyNumber)
{
	// 前回が0で、今回が0でなければトリガー
	if (!mouseStatePre.rgbButtons[keyNumber] && mouseState.rgbButtons[keyNumber]) {
		return true;
	}

	// トリガーでない
	return false;
}

bool Input::IsMousekeyUp(int keyNumber)
{
	/// 前回が0 でなくて、今回が0であればトリガー
	if (!mouseStatePre.rgbButtons[keyNumber] && mouseState.rgbButtons[keyNumber]) {
		return true;
	}

	// トリガーでない
	return false;
}

Vector3 Input::GetMouseMove()
{
	Vector3 tmp = Vector3::Zero();
	tmp.x += (float)mouseState.lX;
	tmp.y += (float)mouseState.lY;
	tmp.z += (float)mouseState.lZ;
	return tmp;
}
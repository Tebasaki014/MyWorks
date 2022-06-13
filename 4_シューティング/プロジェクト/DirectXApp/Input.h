#pragma once

#include <Windows.h>
#include <wrl.h>

#define DIRECTINPUT_VERSION     0x0800          // DirectInputのバージョン指定
#include <dinput.h>

#include"Vector3.h"

/// <summary>
/// 入力
/// </summary>
class Input
{
public:
	struct MouseMove {
		LONG    lX;
		LONG    lY;
		LONG    lZ;
	};

private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public: // メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	/// <returns>成否</returns>
	HRESULT Initialize(HINSTANCE hInstance, HWND hwnd);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// キーの押下をチェック
	/// </summary>
	/// <param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <returns>押されているか</returns>
	bool IsKeyTouch(BYTE keyNumber);

	/// <summary>
	/// キーのトリガーをチェック(押したとき)
	/// </summary>
	/// <param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <returns>トリガーか</returns>
	bool IsKeyDown(BYTE keyNumber);

	/// <summary>
	/// キーのトリガーをチェック(離したとき)
	/// </summary>
	/// <param name="keyNumber">キー番号( DIK_0 等)</param>
	/// <returns>トリガーか</returns>
	bool IsKeyUp(BYTE keyNumber);

	/// <summary>
	/// キーのボタン押下をチェック
	/// </summary>
	/// <returns>押されているか</returns>
	bool IsMousekeyTouch(int keyNumber);

	/// <summary>
	/// キーのボタントリガーをチェック(押したとき)
	/// </summary>
	/// <returns>トリガーか</returns>
	bool IsMousekeyDown(int keyNumber);

	/// <summary>
	/// キーの中ボタントリガーをチェック(離したとき)
	/// </summary>
	/// <returns>トリガーか</returns>
	bool IsMousekeyUp(int keyNumber);

	/// <summary>
	/// マウス移動量を取得
	/// </summary>
	/// <returns>マウス移動量</returns>
	Vector3 GetMouseMove();

private: // メンバ変数
	ComPtr<IDirectInput8> dinput;
	ComPtr<IDirectInputDevice8> devKeyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};
	ComPtr<IDirectInputDevice8> devMouse;
	DIMOUSESTATE2 mouseState = {};
	DIMOUSESTATE2 mouseStatePre = {};
};


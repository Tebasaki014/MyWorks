#pragma once
#include"WatashiEngine.h"
//シーン間で保持する変数
struct CommonData
{
	//エンジン本体
	WatashiEngine* wangine = new WatashiEngine();

	//色とか
	XMFLOAT4 white = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMFLOAT4 red = { 1.0f, 0.0f, 0.0f, 1.0f };
	Color clearColor = { 0.1f,0.25f, 0.5f,0.0f };//画面クリア色(青っぽい色)

};
#pragma once
#include"WatashiEngine.h"
//�V�[���Ԃŕێ�����ϐ�
struct CommonData
{
	//�G���W���{��
	WatashiEngine* wangine = new WatashiEngine();

	//�F�Ƃ�
	XMFLOAT4 white = { 1.0f, 1.0f, 1.0f, 1.0f };
	XMFLOAT4 red = { 1.0f, 0.0f, 0.0f, 1.0f };
	Color clearColor = { 0.1f,0.25f, 0.5f,0.0f };//��ʃN���A�F(���ۂ��F)

};
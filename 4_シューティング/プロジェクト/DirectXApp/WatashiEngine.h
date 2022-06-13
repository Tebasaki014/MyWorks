#pragma once
#include<ctime>
#include<random>

#include"SDelete.h"
#include"Input.h"
#include"Dx12App.h"
#include"FrameRate.h"
#include"Sprite.h"
#include"Object3D.h"
#include"ParticleManager.h"
#include"Audio.h"


#include"Vector2.h"
#include"Vector3.h"
#include"Quaternion.h"

class WatashiEngine
{
public:
	// ���낢��
	WinApp* win = nullptr;
	Dx12App* dx12 = nullptr;
	FrameRate* framerate = nullptr;
	Input* input = nullptr;
	Camera* camera = nullptr;
	bool IsUse2D = true;
	bool IsUse3D = true;

	//������
	void Initialize();
	//��ʃN���A
	bool ScreenClear(Color clearColor);
	//�o�b�t�@�؂�ւ�
	void ScreenFlip();
	//���킨�킨���
	void End();

	//�T�E���h
	//�Đ�
	void PlayWav(const char* filename);

	//�E�B���h�E�T�C�Y�擾
	Vector2 GetWindowSize();

	//�X�v���C�g
	//�`��J�n
	void StartDraw2D();
	//�`��I��
	void EndDraw2D();

	//���f��
	//�`��J�n
	void StartDraw3D();
	//�`��I��
	void EndDraw3D();
};
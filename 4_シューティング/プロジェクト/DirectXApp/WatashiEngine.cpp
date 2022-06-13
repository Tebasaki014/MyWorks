#include "WatashiEngine.h"

void WatashiEngine::Initialize()
{
	win = WinApp::GetInstance();
	win->CreateMainWindow();
	
	dx12 = Dx12App::GetInstance();
	dx12->Initialize(win);

	input = new Input();
	input->Initialize(win->GetHandleInstance(), win->GetHwnd());

	framerate = new FrameRate(60);
	
	if (IsUse2D) { 
		Sprite::StaticInitialize(dx12->GetDevice(), win->window_width, win->window_height);
	}

	if (IsUse3D) { 
		camera = new Camera(win->window_width, win->window_height);
		Object3D::StaticInitialize(dx12->GetDevice(), camera);
		Shader::SetDivice(dx12->GetDevice());
		Light* light = Light::Create(dx12->GetDevice());
		ParticleManager::Create(dx12->GetDevice(), camera);
	}
}

bool WatashiEngine::ScreenClear(Color clearColor)
{
	framerate->Wait();

	if (win->ProcessMessage()) {
		return false;
	}

	dx12->BeginDraw(clearColor);

	input->Update();
	ParticleManager::GetInstance()->Update();

	return true;
}

void WatashiEngine::ScreenFlip()
{
	dx12->EndDraw();
}

void WatashiEngine::End()
{
	ParticleManager::Destroy();
	SDelete(framerate);
	SDelete(camera);
	Light::Destroy();
	win->Terminatewindow();
}

void WatashiEngine::PlayWav(const char* filename)
{
	//audio->PlayWave(filename);
}

Vector2 WatashiEngine::GetWindowSize()
{
	//�E�B���h�E�̒[���擾
	RECT rect;
	GetWindowRect(win->GetHwnd(), &rect);

	//�T�C�Y�ɒ���
	Vector2 result = {};
	result.x = (float)rect.right - (float)rect.left;
	result.y = (float)rect.bottom - (float)rect.top;
	//�g��������(�K��)
	result.x -= 16;
	result.y -= 39;

	return result;
}

void WatashiEngine::StartDraw2D()
{
	//�X�v���C�g�`��O����
	Sprite::PreDraw(dx12->GetCommandList());
}

void WatashiEngine::EndDraw2D()
{
	Sprite::PostDraw();
}

void WatashiEngine::StartDraw3D()
{
	Light::GetInstance()->Update();
	Object3D::PreDraw(dx12->GetCommandList());
}

void WatashiEngine::EndDraw3D()
{
	Object3D::PostDraw();
}
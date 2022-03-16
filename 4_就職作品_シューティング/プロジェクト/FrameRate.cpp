#include "FrameRate.h"
#include "time.h"
#include <windows.h>
FrameRate::FrameRate(int fps)
{
	this->fps = fps;//�Œ肵�����t���[�����[�g
	count = 0;//�t���[����
	startTime = 0;//�������J�n���Ă���̎��Ԃ̋L�^
}
void FrameRate::Update()
{

}
void FrameRate::Wait()
{
	if (count == 0)
	{
		startTime = clock();
	}
	if (count == fps)
	{
		startTime = clock();
		count = 0;
	}
	count++;

	tookTime = clock() - startTime;
	waitTime = count * 1000 / fps - tookTime;
	if (waitTime > 0)
	{
		Sleep(waitTime);
	}
}

#include "FrameRate.h"
#include "time.h"
#include <windows.h>
FrameRate::FrameRate(int fps)
{
	this->fps = fps;//固定したいフレームレート
	count = 0;//フレーム数
	startTime = 0;//処理を開始してからの時間の記録
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

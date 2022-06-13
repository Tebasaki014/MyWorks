#pragma once
#include<time.h>
class Timer
{
private:
	long startTime;
	long nowTime;
public:
	Timer() = default;
	~Timer() = default;

	void CountStart();
	void CountStop();
};
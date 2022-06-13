#pragma once
class FrameRate {

public: 
	FrameRate(int fps);
	void Update();
	void Wait();
private:
	int startTime = 0;
	int count = 0;
	int fps = 0;
	int tookTime = 0;
	int waitTime = 0;
};
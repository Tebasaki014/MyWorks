#pragma once
class Boss
{
public:
	Boss();

	void Update();

	void Boost();
	void Move();
	void Move2();

	void Initialize();

	bool Direc();

	int BossPositionX();
	int BossPositionY();
	int BossWidh();
	int BossHight();
	int BossSenter();
};


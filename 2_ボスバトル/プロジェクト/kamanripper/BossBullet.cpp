#include "DxLib.h"
#include "BossBullet.h"
#include "Boss.h"


Boss boss;

enum Direc
{
	R,
	L,
};

int
bosbulg,
bosbulg2,
bosbulg3,
bullYnum,
prevnum;

float
bobXR,
bobXL,
Y1,
Y2,
Y3,
bobr2,
bobvel,
bobspd;

float bobY;

int bultimer;

Direc direc = Direc::R;

BossBullet::BossBullet(){
	bobr2 = 64;

	bobXR = 0;
	bobXL = 0;
	bobY = 0;

	Y1 = 0;
	Y2 = 0;
	Y3 = 0;

	bobvel = 0;
	bobspd = 25;

	bullYnum = 0;

	bultimer = 0;

	bosbulg = LoadGraph("Resources/teki.png");
	bosbulg2 = LoadGraph("Resources/teki.png");
	bosbulg3 = LoadGraph("Resources/teki.png");
}


void BossBullet::Direc(){
	if (boss.Direc() == 0) { direc = Direc::R; }

	if (boss.Direc() == 1) { direc = Direc::L; }

	bobXR = boss.BossPositionX() + boss.BossWidh();
	bobXL = boss.BossPositionX() - bobr2;
	Y1 = boss.BossPositionY();
	Y2 = boss.BossPositionY() + (boss.BossHight() / 2);
	Y3 = boss.BossPositionY() + (boss.BossHight() - 80);

	bobvel = 0;
	for (int i = 0; i < 3; i++) {
		bullYnum = GetRand(2) + 1;

		if (bullYnum == 1) { bobY = Y1; }
		if (bullYnum == 2) { bobY = Y2; }
		if (bullYnum == 3) { bobY = Y3; }
	}
}

void BossBullet::Update() {
	bobvel = bobspd;

	if (direc == 0) {
		bobXR += bobvel;

		DrawGraph(bobXR, bobY, bosbulg, 0);
	}

	if (direc == 1) {
		bobXL -= bobvel;

		DrawGraph(bobXL, bobY, bosbulg, 0);
	}
}

void BossBullet::out() {
	bobY = 10000;
}

int BossBullet::HX1() {
	if (direc == 0) {
		return bobXR;
	}

	if (direc == 1) {
		return bobXL;
	}
}

int BossBullet::HX2() {
	if (direc == 0) {
		return bobXR + bobr2;
	}

	if (direc == 1) {
		return bobXL + bobr2;
	}
}

int BossBullet::HY1() {
	return bobY;
}

int BossBullet::HY2() {
	return bobY;
}


int BossBullet::JDX1() {
	if (direc == 0) {
		return bobXR - 64;
	}

	if (direc == 1) {
		return bobXL - 128;
	}
}

int BossBullet::JDX2() {
	if (direc == 0) {
		return bobXR + bobr2 + 128;
	}

	if (direc == 1) {
		return bobXL + bobr2 + 64;
	}
}

int BossBullet::JDY1() {
	return bobY - 32;
}

int BossBullet::JDY2() {
	return bobY + 32;
}

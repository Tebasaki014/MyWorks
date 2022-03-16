#include "DxLib.h"
#include "Window.h"
#include "Player.h"
#include "Dice.h"
#include "Boss.h"
#include "BossBullet.h"

int
x1,
x2,
x3,
poX,
poY,
gravity,
velocity,
boost,
atnum,
posnum,
bosgraph,
graphW,
graphH,
graphS,
percent;

int timer = 0;
int boxC = GetColor(255, 255, 255);

Dice dice;
Player bosplayer;
BossBullet bob;
Window win;

enum BossMuki
{
	L,
	R,
};

BossMuki bosmuki = BossMuki::L;

Boss::Boss()
{
	x1 = 1200;
	x2 = 750;
	x3 = 250;

	poX = 1200;
	poY = -510;

	gravity = 1;
	velocity = 0;
	boost = 50;

	atnum = 0;
	posnum = 0;

	percent = 50;

	bosgraph = LoadGraph("Resources/mito.png");
	graphH = 500;
	graphW = 300;
	graphS = graphW / 2;
}

void Boss::Initialize() {
	poX = 1200;
	poY = -510;
}

void Boss::Update() {
	if (bosplayer.PlayerPosX() > poX + graphS) { bosmuki = BossMuki::R; }
	if (bosplayer.PlayerPosX() + bosplayer.PR() < poX + graphS) { bosmuki = BossMuki::L; }

	velocity += gravity;
	poY += velocity;

	if (poY + graphH >= win.windowHight()) {
		poY = 480;
	}

	if (bosmuki == BossMuki::L) {
		DrawExtendGraph(poX, poY, poX + graphW, poY + graphH, bosgraph, 0);
	}
	if (bosmuki == BossMuki::R) {
		DrawExtendGraph(poX + graphW, poY, poX, poY + graphH, bosgraph, 0);
	}
	DrawBox(poX + 50, win.windowHight() - 3, poX + graphW - 50, win.windowHight(), boxC, 1);
}

void Boss::Boost() {
	velocity = -boost;
}

void Boss::Move() {

	posnum = GetRand(2);

	if (velocity == 0) {
		if (posnum == 0) {
			poX = x1;
		}
		if (posnum == 1) {
			poX = x2;
		}
		if (posnum == 2) {
			poX = x3;
		}
	}
}

void Boss::Move2() {
	poX = bosplayer.PlayerPosX() - 20;
}

bool Boss::Direc() {
	if (bosmuki == BossMuki::R) { return 0; }

	if (bosmuki == BossMuki::L) { return 1; }
}

int Boss::BossPositionX() {
	return poX;
}
int Boss::BossPositionY() {
	return poY;
}
int Boss::BossWidh() {
	return graphW;
}
int Boss::BossHight() {
	return graphH;
}
int Boss::BossSenter() {
	return graphH / 2;
}

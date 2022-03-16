#include"DxLib.h"
#include "Bullet.h"
#include "Player.h"

Player bplayer;

enum Direc
{
	R,
	L,
};

int bulgraph;

float
poXR,
poXL,
bpoY,
br2,
vel,
spd;

Direc dir = Direc::R;

Bullet::Bullet()
{
	br2 = 64;

	poXR = 0;
	poXL = 0;
	bpoY = 0;

	vel = 0;
	spd = 130;

	bulgraph = LoadGraph("Resources/tama.png");
}

void Bullet::Direc() {
	if (bplayer.Direc() == 0) { dir = Direc::R; }

	if (bplayer.Direc() == 1) { dir = Direc::L; }

	poXR = bplayer.PlayerPosX() + bplayer.PR();
	poXL = bplayer.PlayerPosX() - br2;
	bpoY = bplayer.PlayerPosY() + 30;

	vel = 0;
}

void Bullet::Update() {
	vel = spd;

	if (dir == 0) {
		poXR += vel;
		DrawGraph(poXR, bpoY, bulgraph, 0);
	}
	if (dir == 1) {
		poXL -= vel;
		DrawGraph(poXL, bpoY, bulgraph, 0);
	}
}

int Bullet::BulletX1() {
	if (dir == 0) {
		return poXR;
	}
	if (dir == 1) {
		return poXL;
	}
}

int Bullet::BulletX2() {
	if (dir == 0) {
		return poXR + br2;
	}
	if (dir == 1) {
		return poXL + br2;
	}
}

int Bullet::BulletY1() {
	return bpoY;
}

int Bullet::BulletY2() {
	return bpoY + br2;
}

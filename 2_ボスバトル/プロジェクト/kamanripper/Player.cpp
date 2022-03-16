#include "Player.h"
#include "DxLib.h"
#include "Window.h"
#include <iostream>

int
prevState,
graph,
bnsn1,
bnsn2,
alpa;

float
poX,
poY,
b1poX,
b2poX,
r2,
gravity,
bgrav,
veloX,
veloY,
b1vel,
b2vel,
speed,
jumpspeed,
bspeed,
shock,
absorb;

enum Muki
{
	Right,
	Left,	
};

Muki muki = Muki::Right;
Window window;
int winX = window.windowWidth();
int winY = window.windowHight();

Player :: Player() {
	poX = 200;//自機初期位置X
    poY = -130;//自機初期位置Y
	b1poX = poX;//分身1初期位置
	b2poX = poX;//分身2初期位置
	r2 = 128;//自機の幅

	gravity = 5;//重力
	bgrav = 5;//分身の減衰度

	speed = 25;//移動速度
	jumpspeed = 70;//ジャンプ力
	bspeed = 50;//分身が飛び出す速度

	veloX = 0;//い　つ　も　の
	veloY = 0;//い　つ　も　の
	b1vel = 0;//い　つ　も　の
	b2vel = 0;//い　つ　も　の

	shock = 0;//反動
	absorb = 8;//反動の減衰度

	prevState = 0;

	alpa = 255;

	SetTransColor(alpa, alpa, alpa);
	graph = LoadGraph("Resources/curepeace_waifu.png");//自機本体
	bnsn1 = LoadGraph("Resources/curepeace_waifu.png");//分身A
	bnsn2 = LoadGraph("Resources/curepeace_waifu.png");//分身B
}

void Player::Initialize() {
	poX = 200;//自機初期位置X
	poY = -130;//自機初期位置Y
}

//基本の挙動
void Player::Update() {

	if (CheckHitKey(KEY_INPUT_D)) {
		veloX = speed;
		muki = Muki::Right;
	}
	else if (CheckHitKey(KEY_INPUT_A)) { 
		veloX = -speed;
		muki = Muki::Left;
	}
	else { veloX = 0; }

	veloX += shock;
	veloY += gravity;

	poX += veloX;
	poY += veloY;

	if (window.Jimen(poY)) { poY = winY - r2; }
	if (window.KabeR(poX)) { poX = winX - r2; }
	if (window.KabeL(poX)) { poX = 0; }

}

//分身の減衰とか
void Player::Bunshin() {
	b1vel += bgrav;
	b2vel -= bgrav;

	b1poX += b1vel;
	b2poX += b2vel;

	if (b1poX >= poX) { b1poX = poX; }
	if (b2poX <= poX) { b2poX = poX; }

	if (Dflag()) {
		b1poX = poX;
		b2poX = poX;
	}
}

//自機関連の描画処理
void Player::Draw() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpa);
	if (muki == Muki::Right) {
		DrawExtendGraph(b1poX, poY, b1poX + r2, poY + r2, bnsn1, 0);
		DrawExtendGraph(b2poX, poY, b2poX + r2, poY + r2, bnsn2, 0);
		DrawExtendGraph(poX, poY, poX + r2, poY + r2, graph, 0);
	}
	if (muki == Muki::Left) {
		DrawExtendGraph(b1poX + r2, poY, b1poX, poY + r2, bnsn1, 0);
		DrawExtendGraph(b2poX + r2, poY, b2poX, poY + r2, bnsn2, 0);
		DrawExtendGraph(poX + r2, poY, poX, poY + r2, graph, 0);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpa);
}

//ジャンプ
void Player :: Jump() {
	veloY = -jumpspeed;
}

//ジャンプできるか
bool Player :: Jflag() {
	if (window.Jimen(poY)) { return true; }
	else { return false; }
}

//反動　自機を後ろにふっとばす
void Player::Sstart() {
	if (muki == Muki::Right) {
		shock = -100;
		prevState = 0;
	}
	if (muki == Muki::Left) {
		shock = 100;
		prevState = 1;
	}
}

//Sstartでふっとばされた後 減衰
void Player::Shot() {
	if (muki == Muki::Right) {
		shock += absorb;
	}
	if (muki == Muki::Left) {
		shock -= absorb;
	}

	if (Sflag()) { shock = 0; }
}

//反動停止処理
bool Player::Sflag() {
	if (shock >= 0 && prevState == 0) { return true; }
	if (shock <= 0 && prevState == 1) { return true; }
	else return false;
}

//分身を出す
void Player::Dodge() {
	alpa = 120;

	b1vel = -bspeed;
	b2vel = bspeed;
}

//分身停止処理
bool Player::Dflag() {
	if (b2vel <= 0) { return true; }
	else return false;
}

//自機の幅
int Player::PR() {
	return r2;
}

//自機のX座標
int Player::PlayerPosX() {
	return poX;
}

//自機のY座標
int Player::PlayerPosY() {
	return poY;
}

int Player::PlayerPosX2() {
	return poX + r2;
}

int Player::PlayerPosY2() {
	return poY + r2;
}

int Player::PLayerJDX() {
	return poX - 64;
}

int Player::PlayerJDX2() {
	return poX + r2 + 64;
}

int Player::PlayerJDY() {
	return poY - 64;
}

int Player::PlayerJDY2() {
	return poY + r2 + 64;
}

//右向きなら0 左向きなら1
bool Player::Direc() {
	if (muki == Muki::Right) { return 0; }
	if (muki == Muki::Left) { return 1; }
}

int Player::PlayerAlpa() {
	return alpa;
}



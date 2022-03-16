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
	poX = 200;//���@�����ʒuX
    poY = -130;//���@�����ʒuY
	b1poX = poX;//���g1�����ʒu
	b2poX = poX;//���g2�����ʒu
	r2 = 128;//���@�̕�

	gravity = 5;//�d��
	bgrav = 5;//���g�̌����x

	speed = 25;//�ړ����x
	jumpspeed = 70;//�W�����v��
	bspeed = 50;//���g����яo�����x

	veloX = 0;//���@�@���@��
	veloY = 0;//���@�@���@��
	b1vel = 0;//���@�@���@��
	b2vel = 0;//���@�@���@��

	shock = 0;//����
	absorb = 8;//�����̌����x

	prevState = 0;

	alpa = 255;

	SetTransColor(alpa, alpa, alpa);
	graph = LoadGraph("Resources/curepeace_waifu.png");//���@�{��
	bnsn1 = LoadGraph("Resources/curepeace_waifu.png");//���gA
	bnsn2 = LoadGraph("Resources/curepeace_waifu.png");//���gB
}

void Player::Initialize() {
	poX = 200;//���@�����ʒuX
	poY = -130;//���@�����ʒuY
}

//��{�̋���
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

//���g�̌����Ƃ�
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

//���@�֘A�̕`�揈��
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

//�W�����v
void Player :: Jump() {
	veloY = -jumpspeed;
}

//�W�����v�ł��邩
bool Player :: Jflag() {
	if (window.Jimen(poY)) { return true; }
	else { return false; }
}

//�����@���@�����ɂӂ��Ƃ΂�
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

//Sstart�łӂ��Ƃ΂��ꂽ�� ����
void Player::Shot() {
	if (muki == Muki::Right) {
		shock += absorb;
	}
	if (muki == Muki::Left) {
		shock -= absorb;
	}

	if (Sflag()) { shock = 0; }
}

//������~����
bool Player::Sflag() {
	if (shock >= 0 && prevState == 0) { return true; }
	if (shock <= 0 && prevState == 1) { return true; }
	else return false;
}

//���g���o��
void Player::Dodge() {
	alpa = 120;

	b1vel = -bspeed;
	b2vel = bspeed;
}

//���g��~����
bool Player::Dflag() {
	if (b2vel <= 0) { return true; }
	else return false;
}

//���@�̕�
int Player::PR() {
	return r2;
}

//���@��X���W
int Player::PlayerPosX() {
	return poX;
}

//���@��Y���W
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

//�E�����Ȃ�0 �������Ȃ�1
bool Player::Direc() {
	if (muki == Muki::Right) { return 0; }
	if (muki == Muki::Left) { return 1; }
}

int Player::PlayerAlpa() {
	return alpa;
}



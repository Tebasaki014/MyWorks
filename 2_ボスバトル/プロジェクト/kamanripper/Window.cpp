#include "Window.h"
#include "DxLib.h"
#include "Player.h"

int width;
int hight;

Player player;

Window::Window()
{
	width = 1792;
	hight = 960;
}

//��ʊO�Ȃ�false
bool Window :: Outside(int poX, int poY) {
	if (poX >= 0 || poX <= width || poY >= 0 || poY <= hight) {
		return true;
	}
	else{
		return false;
	}
}

//��ʉ��[�ɐڂ��Ă�����true
bool Window :: Jimen(int poY) {
	if (poY >= hight - player.PR()) {
		return true;
	}
	else	{
		return false;
	}
}

//��ʏ�[�ɐڂ��Ă�����true
bool Window::Tenjo(int poY) {
	if (poY <= 0) {
		return true;
	}
	else {
		return false;
	}
}

//��ʉE�[�ɐڂ��Ă�����true
bool Window::KabeR(int poX) {
	if (poX >= width - player.PR()) {
		return true;
	}
	else {
		return false;
	}
}

//��ʍ��[�ɐڂ��Ă�����true
bool Window::KabeL(int poX) {
	if (poX <= 0) {
		return true;
	}
	else {
		return false;
	}
}

//��ʕ�
int Window::windowWidth() {
	return width;
}
//��ʍ���
int Window::windowHight() {
	return hight;
}

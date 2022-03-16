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

//画面外ならfalse
bool Window :: Outside(int poX, int poY) {
	if (poX >= 0 || poX <= width || poY >= 0 || poY <= hight) {
		return true;
	}
	else{
		return false;
	}
}

//画面下端に接していたらtrue
bool Window :: Jimen(int poY) {
	if (poY >= hight - player.PR()) {
		return true;
	}
	else	{
		return false;
	}
}

//画面上端に接していたらtrue
bool Window::Tenjo(int poY) {
	if (poY <= 0) {
		return true;
	}
	else {
		return false;
	}
}

//画面右端に接していたらtrue
bool Window::KabeR(int poX) {
	if (poX >= width - player.PR()) {
		return true;
	}
	else {
		return false;
	}
}

//画面左端に接していたらtrue
bool Window::KabeL(int poX) {
	if (poX <= 0) {
		return true;
	}
	else {
		return false;
	}
}

//画面幅
int Window::windowWidth() {
	return width;
}
//画面高さ
int Window::windowHight() {
	return hight;
}

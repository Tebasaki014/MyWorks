#include "DxLib.h"
#include "Dice.h"

int result;

Dice::Dice()
{
	result = 0;
}

//������(��)�𓊂��Đ��������s�����肷��
bool Dice::Result(int percentage) {
	result = GetRand(99) + 1;

	if (percentage >= result) { return true; }
	else { return false; }
}

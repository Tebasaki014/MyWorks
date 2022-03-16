#include "DxLib.h"
#include "Dice.h"

int result;

Dice::Dice()
{
	result = 0;
}

//¬Œ÷—¦(“)‚ğ“Š‚°‚Ä¬Œ÷‚©¸”s‚©”»’è‚·‚é
bool Dice::Result(int percentage) {
	result = GetRand(99) + 1;

	if (percentage >= result) { return true; }
	else { return false; }
}

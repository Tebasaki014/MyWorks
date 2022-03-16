#include "CheckHitSquare.h"



CheckHitSquare::CheckHitSquare()
{
}

//2つの四角形の2点をそれぞれ投げ、当たり判定を返す
bool CheckHitSquare::result(int obj1X1, int  obj1Y1, int obj1X2, int obj1Y2,
	int obj2X1, int obj2Y1, int obj2X2, int obj2Y2) {

	if (((obj1X1 > obj2X1 && obj1X1 < obj2X2) ||
		(obj2X1 > obj1X1 && obj2X1 < obj1X2)) &&
		((obj1Y1 > obj2Y1 && obj1Y1 < obj2Y2) ||
		(obj2Y1 > obj1Y1 && obj2Y1 < obj1Y2))) {

		return true;
	}
	else { return false; }
}

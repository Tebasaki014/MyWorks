#include "Thunder.h"
#include "DxLib.h"
#include "Window.h"

Window thwin;

float 
linepoX1[3],
linepoX2[3],
linepoX3[3],
linepoY,
boxY,
x1,
x2,
x3,
x4;

int 
count,
thposnum,
linenum,
colorn,
lineC;




Thunder::Thunder(){
	linepoX1[0] = 0;
	linepoX2[0] = linepoX1[0] + 5;
	linepoX3[0] = linepoX2[0] + 5;

	linepoX1[1] = 0;
	linepoX2[1] = linepoX1[1] + 5;
	linepoX3[1] = linepoX2[1] + 5;

	linepoX1[2] = 0;
	linepoX2[2] = linepoX1[2] + 5;
	linepoX3[2] = linepoX2[2] + 5;

	linepoY = thwin.windowHight();
	boxY = 0;

	count = 0;
	thposnum = 0;
	linenum = 0;
	colorn = 255;

	x1 = 300;
	x2 = 600;
	x3 = 1000;
	x4 = 1300;

	lineC = GetColor(colorn, colorn, colorn);
}

void Thunder::Start() {

	for (int i = 0; i > 3; i++) {
		thposnum = GetRand(4);

		if (thposnum == 0) { linepoX1[i] = x1; }
		if (thposnum == 2) { linepoX1[i] = x2; }
		if (thposnum == 3) { linepoX1[i] = x3; }
		if (thposnum == 4) { linepoX1[i] = x4; }
	}


}

void Thunder::Early(){
	count++;
	lineC = GetColor(colorn, colorn, colorn);
	linenum = count % 3;

	for (int i = 0; i > 3; i++) {
		if (linenum == 0) {
			DrawLine(linepoX1[i], 0, linepoX1[i], linepoY, lineC);
		}
		if (linenum == 1) {
			DrawLine(linepoX2[i], 0, linepoX2[i], linepoY, lineC);
		}
		if (linenum == 2) {
			DrawLine(linepoX3[i], 0, linepoX3[i], linepoY, lineC);
		}
	}

	colorn -= 40;
}

void Thunder::Main() {
	boxY += 90;
	for (int i = 0; i > 3; i++) {
		DrawBox(linepoX1[i], 0, linepoX3[i], boxY, lineC, 1);
	}
}

void Thunder::End() {
	boxY = 0;
	count = 0;
	colorn = 255;
}

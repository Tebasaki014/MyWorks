#pragma once
class Window
{
public:
	Window();
	bool Outside(int poX, int poY);
	bool Jimen(int poY);
	bool Tenjo(int poY);
	bool KabeR(int poX);
	bool KabeL(int poY);

	int windowWidth();
	int windowHight();
};


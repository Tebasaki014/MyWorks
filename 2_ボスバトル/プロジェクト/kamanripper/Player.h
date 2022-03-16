#pragma once

class Player
{
public:
	Player();
	void Initialize();
	void Update();
	void Bunshin();
	void Draw();

	void Jump();
	bool Jflag();

	void Sstart();
	void Shot();
	bool Sflag();

	void Dodge();
	bool Dflag();

	int PR();
	int PlayerPosX();
	int PlayerPosY();
	int PlayerPosX2();
	int PlayerPosY2();

	int PLayerJDX();
	int PlayerJDY();
	int PlayerJDX2();
	int PlayerJDY2();

	bool Direc();
	int PlayerAlpa();
};
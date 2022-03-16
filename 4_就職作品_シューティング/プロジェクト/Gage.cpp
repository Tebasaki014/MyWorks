#include "Gage.h"

float RateClamp(const float& num, const float& min, const float& max) {
	if (num <= min || num >= max) {
		if (num <= min) {
			return min;
		}
		if (num >= max) {
			return max;
		}
		else return num;
	}
	else return num;
}

#pragma region Gage
void Gage2D::Draw()
{
	if (isView) {
		if (isViewBase2) { base2->Draw(color); }
		if (isViewBar)   { bar->Draw(color); }
		if (isViewBase)  { base->Draw(color); }
		if (isViewBar2)  { bar2->Draw(color); }
	}
}

void Gage2D::End()
{
	SDelete(base2);
	SDelete(bar2);
	SDelete(bar);
	SDelete(base);
}
#pragma endregion

#pragma region CircleGage2D
CircleGage2D::CircleGage2D(const Vector2& position, const float& size)
{
	Texture texGage = 1;
	Texture texBase = 2;

	this->position = position;
	this->spSize = { size, size };

	Sprite::LoadTexture(texGage, L"Resources/CircleGageWide.png");
	Sprite::LoadTexture(texBase, L"Resources/CircleGageWideBase.png");
	bar = Sprite::Create(texGage, position, color, Vector2(0.5f, 0.5f));
	bar2 = Sprite::Create(texGage, position, color, Vector2(0.5f, 0.5f));
	base = Sprite::Create(texBase, position, color, Vector2(0.5f, 0.5f));
	base2 = Sprite::Create(texBase, position, color, Vector2(0.5f, 0.5f), 1);


	bar->SetSize(spSize);
	bar2->SetSize(spSize);
	base->SetSize(spSize);
	base2->SetSize(spSize);
}

void CircleGage2D::Start()
{

}

void CircleGage2D::Update(const float& rate)
{
	gageRate = rate;
	gageRate = RateClamp(gageRate, 0.0f, 1.0f);
	rot = 360.0f * gageRate;

	if (gageRate <= 0.5f) {
		isViewBar2 = false;
		halfrot = rot;
	}
	else {
		isViewBar2 = true;
		halfrot = 180.0f;
	}

	SpriteUpdate();
}

void CircleGage2D::SpriteUpdate()
{
	bar->SetPosition(position);
	bar2->SetPosition(position);
	base->SetPosition(position);
	base2->SetPosition(position);

	bar->SetRotation(halfrot);
	bar2->SetRotation(rot);

	bar->SetSize(spSize);
	bar2->SetSize(spSize);
	base->SetSize(spSize);
	base2->SetSize(spSize);
}
#pragma endregion
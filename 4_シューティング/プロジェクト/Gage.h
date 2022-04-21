#pragma once
#include "WatashiEngine.h"
class Gage2D
{
public:

	Gage2D() = default;
	~Gage2D() = default;

	virtual void Start() = 0;
	virtual void Update(const float& rate) = 0;
	virtual void Draw();
	virtual void End();

	inline void SetColor(DirectX::XMFLOAT4 color) {
		this->color = color;
	}

	bool isView = true;
	Sprite* bar = nullptr;
	Sprite* bar2 = nullptr;
	Sprite* base = nullptr;
	Sprite* base2 = nullptr;

	Vector2 position = {};
	
	DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f };
protected:
	Vector2 spSize = { 100.0f, 100.0f };
	bool isViewBar = true;
	bool isViewBar2 = true;
	bool isViewBase = true;
	bool isViewBase2 = true;

	float gageRate = 0.0f;
};

class CircleGage2D : public Gage2D
{
public:
	CircleGage2D(const Vector2& position, const float& size);
	~CircleGage2D() { this->End(); }

	void Start() override;
	void Update(const float& rate) override;

	
	inline void SetSize(float size) {
		spSize = { size, size };
	}

private:
	void SpriteUpdate();

	float rot = 0.0f;
	float halfrot = 0.0f;
};
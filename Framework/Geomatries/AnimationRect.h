#pragma once

#include "TextureRect.h"

class AnimationRect : public TextureRect
{
public:
	AnimationRect(Vector3 position, Vector3 size);
	~AnimationRect();

	void Update();
	void Render();

	virtual void Move() override;
	virtual void Follow(const Vector3 st, const Vector3 direc);

	void SetAnimator(class Animator* animator) { this->animator = animator; }
	void SetSpeed(const int speed) { this->speed = speed; }
	Vector3 GetmoveP() { return moveP; }
private:
	
	void SetNormalize(D3DXVECTOR2 move, const int speed, const float delta);

	int speed;
	Vector3 moveP;
	class Animator* animator = nullptr;

	ID3D11SamplerState* point[2];
	ID3D11BlendState* bPoint[2];
};
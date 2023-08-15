#pragma once

class Game_Master;
class Character_Master : public Game_Master
{
public:
	Character_Master();
	~Character_Master();

	virtual void Update();
	virtual void Render();
	void Chack_Collision();
	void Chack_HP();
};
#pragma once

class Game_Master : public IGame_Master
{
public:
	Game_Master();
	~Game_Master();
	void Chack_ALL_LIST();

	void Update();
	void Render();

};

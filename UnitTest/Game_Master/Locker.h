#pragma once
class Locker
{
public:
	Locker();
	~Locker();
	void Update();
	void Render();

private:
	int MaxSize;
	std::list<ICard_UI*> UI_list;
};


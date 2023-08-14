#pragma once

class Game_Demo : public IObject
{
public:
	virtual void Init() override;
	virtual void Destroy() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUI() override;

private:
	Game_Master* GM = nullptr;
	MousePointer* mp = nullptr;
	Card_Demo* cd = nullptr;
	Character_Master* ef = nullptr;
	UI_Master* ui = nullptr;
};
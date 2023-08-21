#pragma once

class Ready_Ui : public IGame_Master
{
public:
	Ready_Ui();
	~Ready_Ui();
	void Update();

private:
	int Goldcount;
	int Gold_Max;
	std::vector<UI_Obejct*> Gold;

	int LevelUpCost;
	int Levelcount;
	int Level_Max;
	std::vector<UI_Obejct*> Level;

	Vector3 Buttonoffset;
	Vector3 LBaseposition;
	Vector3 RBaseposition;
	Vector3 Buttonsize;

	Vector3 Level_UI_size;
	Vector3 Gold_UI_size;

	// 상점 새로고침 버튼
	Button* ReButton = nullptr;

	// 전투준비 버튼
	Button* ReadyButton = nullptr;

	// 상점단계 업그레이드 버튼
	Button* UpgradeButton = nullptr;

	// 상점 잠금 버튼
	Button* LockButton = nullptr;

	// 카메라를 기준으로 Texture2D의 position을 수정해줌
	Vector3 GetCMPosition(const Vector3 Basepositon, const Vector3 size, const Vector3 offset, const float x, const float y);

	// 지정된 Level최대값을 기준으로 Level을 상승시킴.
	void LevelUP(const bool Press);
	
	// 지정된 Gold최대값을 기준으로 Gold를 상승시킴
	void GoldUP(const bool Press);
};

